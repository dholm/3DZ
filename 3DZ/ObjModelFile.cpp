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
#include <sstream>
#include <iterator>

#include <3DZ/Vector.hpp>
#include <3DZ/StringUtils.hpp>

#include "ObjModelFile.hpp"

namespace TDZ {

	ObjModelFile::operator Model() const {
		Model model;

		model.setName(m_name);

		for (NameGroupMap::const_iterator it(m_groupMap.begin()); it != m_groupMap.end(); ++it) {
			Mesh mesh;
			groupToMesh(it->second, mesh);
			model.pushMesh(it->first, mesh);
		}
		return model;
	}

	bool ObjModelFile::load(const std::string& path) {
		std::ifstream objFile(path.c_str());
		if (!objFile) {
			return false;
		}

		ObjGroup objGroup;
		std::string word;
		for (std::string word; objFile >> word; ) {
			if (word == "v") {
				loadVertex(objFile, objGroup);
			} else if (word == "vt") {
				loadTextureVertex(objFile, objGroup);
			} else if (word == "vn") {
				loadNormal(objFile, objGroup);
			} else if (word == "f") {
				if (!loadFace(objFile, objGroup)) {
					return false;
				}
			} else if (word == "g") {
				loadGroup(objFile, objGroup);
			} else if (word == "o") {
				std::getline(objFile, m_name);
				m_name = trim(m_name);
			} else if (word == "mtllib") {
				/* Load material */
				assert(false);
			} else {
				/* Skip */
				std::string line;
				std::getline(objFile, line);
			}
			word.clear();
		}
		pushGroup(objGroup);
		
		return true;
	}
	
	void ObjModelFile::loadVertex(std::istream& objStream, ObjGroup& objGroup) const {
		Mesh::Vertex v;
		v[0] = v[1] = v[2] = 0.0f;
		objStream >> v[0] >> v[1] >> v[2];
		objGroup.m_vertices.push_back(v);
	}

	void ObjModelFile::loadTextureVertex(std::istream& objStream, ObjGroup& objGroup) const {
		Mesh::Vertex v;
		v[0] = v[1] = v[2] = 0.0f;
		objStream >> v[0] >> v[1] >> v[2];
		objGroup.m_textureVertices.push_back(v);
	}

	void ObjModelFile::loadNormal(std::istream& objStream, ObjGroup& objGroup) const {
		Mesh::Vertex v;
		v[0] = v[1] = v[2] = 0.0f;
		objStream >> v[0] >> v[1] >> v[2];
		objGroup.m_normals.push_back(v);
	}
	
	bool ObjModelFile::loadFace(std::istream& objStream, ObjGroup& objGroup) const {
		std::string line;
		std::getline(objStream, line);
		std::stringstream lineStream(line);
		for (
			std::istream_iterator<std::string> it(lineStream), end;
			it != end;
			++it
		) {
			Face face;
			int type = FaceType_V;
			std::stringstream faceStrStream(*it);
			while (faceStrStream) {
				char slash('/');
				faceStrStream >> face[type] >> slash;
				--face[type++];
				
				if (FaceType_VN < type) {
					return false;
				}
			}
			objGroup.m_faces.push_back(face);
		}
		
		return true;
	}

	void ObjModelFile::loadGroup(std::istream& objStream, ObjGroup& objGroup) {
		pushGroup(objGroup);
		
		objGroup = ObjGroup();
		std::getline(objStream, objGroup.m_name);
		objGroup.m_name = trim(objGroup.m_name);
	}

	void ObjModelFile::pushGroup(const ObjGroup& objGroup) {
		if (!objGroup.m_name.empty()) {
			m_groupMap[objGroup.m_name] = objGroup;
		}
	}
	
	void ObjModelFile::groupToMesh(const ObjGroup& group, Mesh& outMesh) const {
		for (FaceVec::const_iterator it(group.m_faces.begin()); it != group.m_faces.end(); ++it) {
			if (0 <= (*it)[0] && (*it)[0] < group.m_vertices.size()) {
				outMesh.pushVertex(group.m_vertices[(*it)[0]]);
			}
			if (0 <= (*it)[1] && (*it)[1] < group.m_textureVertices.size()) {
				outMesh.pushTextureVertex(group.m_textureVertices[(*it)[1]]);
			}
			if (0 <= (*it)[2] && (*it)[2] < group.m_normals.size()) {
				outMesh.pushNormal(group.m_normals[(*it)[2]]);
			}
		}
	}
} // TDZ
