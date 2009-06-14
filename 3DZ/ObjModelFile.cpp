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

#include "ObjModelFile.hpp"

namespace TDZ {
	
	ObjModelFile::ObjModelFile() :
		Model(),
		m_vertices(),
		m_textureVertices(),
		m_normals(),
		m_faces(),
		m_groups()
	{
	}

	bool ObjModelFile::load(const std::string& path) {
		std::ifstream objFile(path.c_str());
		if (!objFile) {
			return false;
		}
		
		while (objFile) {
			char buffer[256] = {0, };
			objFile.getline(buffer, sizeof(buffer));
			std::string line = std::string(buffer);
			line = line.substr(0, line.find('#'));
			
			if (line.empty()) {
				continue;
			}
			
			switch (line[0]) {
				case 'v':
					if (!loadVertex(line)) {
						return false;
					}
					break;
					
				case 'g':
					if (!loadGroup(line)) {
						return false;
					}
					break;
					
				case 'f':
					if (!loadFace(line)) {
						return false;
					}
					break;
					
				default:
					std::cerr << "obj invalid [" << line << "]" << std::endl;
					return false;
			}
		}
		
		return true;
	}
	
	bool ObjModelFile::loadVertex(const std::string& line) {
		assert(line[0] == 'v');
		
		char dummy[10] = {0, };
		Vector3f v;
		v[0] = v[1] = v[2] = 0.0f;
		sscanf(line.c_str(), "%s %f %f %f", dummy, &v[0], &v[1], &v[2]);

		switch (line[1]) {
			case ' ':
				m_vertices.push_back(v);
				break;
				
			case 't':
				m_textureVertices.push_back(v);
				break;
				
			case 'n':
				m_normals.push_back(v);
				break;
				
			default:
				std::cerr << "loadv incorrect [" << line << "]" <<std::endl;
				return false;
		}
		
		return true;
	}
	
	bool ObjModelFile::loadGroup(const std::string& line) {
		assert(line[0] == 'g');
		
		std::string strLine(line.substr(0, line.length() - 1));

		for (
			std::string::size_type leftPos(strLine.find(" "));
			leftPos != std::string::npos;
			leftPos = strLine.find(" ", leftPos)
		) {
			std::string::size_type rightPos(strLine.find(" ", ++leftPos));
			
			std::string word;
			if (rightPos != std::string::npos) {
				word = strLine.substr(leftPos, rightPos - leftPos);
			} else {
				word = strLine.substr(leftPos, strLine.length());
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
		
		std::string strLine(line.substr(0, line.length() - 1));
		
		Face face = {0, };
		for (
			std::string::size_type leftPos(strLine.find(" "));
			leftPos != std::string::npos;
			leftPos = strLine.find(" ", leftPos)
		) {
			std::string::size_type rightPos(strLine.find(" ", ++leftPos));

			std::string word;
			if (rightPos != std::string::npos) {
				word = strLine.substr(leftPos, rightPos - leftPos);
			} else {
				word = strLine.substr(leftPos);
			}

			if (word != " ") {
				std::string::size_type posSlash1 = word.find("/");
				std::string::size_type posSlash2 = word.find("/", posSlash1 + 1);
				sscanf(word.substr(0, posSlash1).c_str(), "%d", &face.m_vertexIndex);
				if (posSlash1 + 1 < posSlash2) {
					sscanf(word.substr(posSlash1 + 1, posSlash2 - (posSlash1 + 1)).c_str(), "%d", &face.m_textureVertexIndex);
				} else {
					face.m_textureVertexIndex = 0;
				}
				
				if (posSlash2 + 1 < word.length()) {
					sscanf(word.substr(posSlash2 + 1, word.length()).c_str(), "%d", &face.m_normalIndex);
				} else {
					face.m_normalIndex = 0;
				}
				
				--face.m_vertexIndex;
				--face.m_textureVertexIndex;
				--face.m_normalIndex;
				
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
