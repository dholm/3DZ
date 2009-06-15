/*
 *  ObjModelFile.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <cassert>
#include <fstream>

#include <3DZ/StringUtils.hpp>

#include "ObjModelFile.hpp"

namespace TDZ {
	
	ObjModelFile::ObjModelFile() :
		Mesh(),
		m_groups()
	{
	}

	bool ObjModelFile::load(const std::string& path) {
		std::ifstream objFile(path.c_str());
		if (!objFile) {
			return false;
		}

		std::string word;
		while (objFile >> word) {
			switch (word[0]) {
				case 'v':
					if (word == "v" && !loadVertex(objFile)) {
						return false;
					} else if (word == "vt" && !loadTextureVertex(objFile)) {
						return false;
					} else if (word == "vn" && !loadNormal(objFile)) {
						return false;
					} else {
						return false;
					}
					break;
					
				case 'f':
					if (!loadFace(objFile)) {
						return false;
					}
					break;
					
				case 'g':
					if (!loadGroup(objFile)) {
						return false;
					}
					break;
					
				case 'o':
					objFile >> m_name;
					break;
					
				case 'm':
					/* Load material */
					break;
					
				default:
					std::getline(objFile, word); // Skip
			}
			word.clear();
		}
		
		return true;
	}
	
	bool ObjModelFile::loadVertex(std::istream& objStream) {
		Vertex v;
		v[0] = v[1] = v[2] = 0.0f;
		objStream >> v[0] >> v[1] >> v[2];
		m_vertices.push_back(v);
	}

	bool ObjModelFile::loadTextureVertex(std::istream& objStream) {
		Vertex v;
		v[0] = v[1] = v[2] = 0.0f;
		objStream >> v[0] >> v[1] >> v[2];
		m_textureVertices.push_back(v);
	}

	bool ObjModelFile::loadNormal(std::istream& objStream) {
		Vertex v;
		v[0] = v[1] = v[2] = 0.0f;
		objStream >> v[0] >> v[1] >> v[2];
		m_normals.push_back(v);
	}
	
	bool ObjModelFile::loadGroup(std::istream& objStream) {
		std::string name;
		std::getline(objStream, name);
		objStream >> name;
		
		assert(line[0] == 'g');
		
		for (
			std::string::size_type leftPos(line.find(" "));
			leftPos != std::string::npos;
			leftPos = line.find(" ", leftPos)
		) {
			std::string::size_type rightPos(line.find(" ", ++leftPos));
			
			std::string word;
			if (rightPos != std::string::npos) {
				word = line.substr(leftPos, rightPos - leftPos);
			} else {
				word = line.substr(leftPos, line.length());
			}
			
			if (word != " ") {
				NameGroupMap::const_iterator it(m_groups.find(word));
				if (it == m_groups.end()) {
					Group group;
					group.m_name = word;
					group.m_currentSmoothingGroupKey = -1;
					group.m_faces = 0;
					
					m_groups[word] = group;
					it = m_groups.find(word);
				}
			}
		}
		
		return true;
	}
	
	bool ObjModelFile::loadFace(const std::string& line) {
		assert(line[0] == 'f');
		
		Face face;
		for (
			std::string::size_type leftPos(line.find(" "));
			leftPos != std::string::npos;
			leftPos = line.find(" ", leftPos)
		) {
			std::string::size_type rightPos(line.find(" ", ++leftPos));

			std::string word;
			if (rightPos != std::string::npos) {
				word = line.substr(leftPos, rightPos - leftPos);
			} else {
				word = line.substr(leftPos);
			}

			if (word != " ") {
				std::string::size_type posSlash1 = word.find("/");
				std::string::size_type posSlash2 = word.find("/", posSlash1 + 1);
				sscanf(word.substr(0, posSlash1).c_str(), "%d", &face[0]);
				if (posSlash1 + 1 <= posSlash2) {
					sscanf(word.substr(posSlash1 + 1, posSlash2 - (posSlash1 + 1)).c_str(), "%d", &face[1]);
				} else {
					face[1] = 0;
				}
				
				if (posSlash2 + 1 <= word.length()) {
					sscanf(word.substr(posSlash2 + 1, word.length()).c_str(), "%d", &face[2]);
				} else {
					face[2] = 0;
				}
				
				--face[0];
				--face[1];
				--face[2];
				
				m_faces.push_back(face);
			}
		}
		
		if (m_groups.empty()) {
			Group group = {0, };
			group.m_name = "default";
			m_groups["default"] = group;
		}
		
		for (
			NameGroupMap::iterator groupIt(m_groups.begin());
			groupIt != m_groups.end();
			++groupIt
		) {
			if (groupIt->second.m_smoothingGroups.empty()) {
				IdSmoothingGroupMap::iterator smoothingGroupIt(groupIt->second.m_smoothingGroups.find(0));
				if (smoothingGroupIt == groupIt->second.m_smoothingGroups.end()) {
					SmoothingGroup smoothingGroup = {0, };
					smoothingGroup.m_id = 0;
					groupIt->second.m_smoothingGroups[0] = smoothingGroup;
				}
				groupIt->second.m_currentSmoothingGroupKey = 0;
			}
			
			groupIt->second.m_smoothingGroups[groupIt->second.m_currentSmoothingGroupKey].m_faces.push_back(face);
			++groupIt->second.m_faces;
		}
		
		return true;
	}
} // TDZ
