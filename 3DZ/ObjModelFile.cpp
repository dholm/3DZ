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

#include "Vector.hpp"
#include "StringUtils.hpp"
#include "Material.hpp"
#include "Model.hpp"
#include "MtlMaterialFile.hpp"
#include "ObjModelFile.hpp"

namespace TDZ {

	ObjModelFile::operator Model() const {
		Model model;

		model.setName(m_name);

		return model;
	}

	bool ObjModelFile::load(const std::string& path, TextureManager& textureManager) {
		std::ifstream objFile(path.c_str());
		if (!objFile) {
			return false;
		}

		Mesh::VertexVec vertices;
		Mesh::VertexVec textureVertices;
		Mesh::VertexVec normals;
		NameGroupMap groupMap;
		
		ObjGroup objGroup;
		std::string word;
		for (std::string word; objFile >> word; ) {
			if (word == "v") {
				loadVertex(objFile, vertices);
			} else if (word == "vt") {
				loadTextureVertex(objFile, textureVertices);
			} else if (word == "vn") {
				loadNormal(objFile, normals);
			} else if (word == "f") {
				if (!loadFace(objFile, objGroup)) {
					return false;
				}
			} else if (word == "g") {
				loadGroup(objFile, objGroup, groupMap);
			} else if (word == "o") {
				std::getline(objFile, word);
				setName(trim(word));
			} else if (word == "mtllib") {
				if (!(objFile >> word)) {
					return false;
				}
				
				MtlMaterialFile materialFile;
				const std::string materialFilePath((path.substr(0, path.find_last_of("/")) + "/") + trim(word));
				if (!materialFile.load(materialFilePath, textureManager, *this)) {
					return false;
				}
			} else if (word == "usemtl") {
				if (!(objFile >> word)) {
					return false;
				}
				objGroup.m_materialName = trim(word);
			} else {
				/* Skip */
				std::string line;
				std::getline(objFile, line);
			}
			word.clear();
		}
		pushGroup(objGroup, groupMap);
		
		for (NameGroupMap::const_iterator it(groupMap.begin()); it != groupMap.end(); ++it) {
			Mesh mesh;
			mesh.setMaterialName(it->second.m_materialName);
			for (FaceVec::const_iterator faceIt(it->second.m_faces.begin()); faceIt != it->second.m_faces.end(); ++faceIt) {
				if (0 <= (*faceIt)[0] && (*faceIt)[0] < vertices.size()) {
					mesh.pushVertex(vertices[(*faceIt)[0]]);
				}
				if (0 <= (*faceIt)[1] && (*faceIt)[1] < textureVertices.size()) {
					mesh.pushTextureVertex(textureVertices[(*faceIt)[1]]);
				}
				if (0 <= (*faceIt)[2] && (*faceIt)[2] < normals.size()) {
					mesh.pushNormal(normals[(*faceIt)[2]]);
				}
			}
			pushMesh(it->first, mesh);
		}
		
		return true;
	}
	
	void ObjModelFile::loadVertex(std::istream& objStream, Mesh::VertexVec& vertices) {
		Mesh::Vertex v;
		v[0] = v[1] = v[2] = 0.0f;
		objStream >> v[0] >> v[1] >> v[2];
		vertices.push_back(v);
	}

	void ObjModelFile::loadTextureVertex(std::istream& objStream, Mesh::VertexVec& textureVertices) {
		Mesh::Vertex v;
		objStream >> v[0] >> v[1];
		textureVertices.push_back(v);
	}

	void ObjModelFile::loadNormal(std::istream& objStream, Mesh::VertexVec& normals) {
		Mesh::Vertex v;
		v[0] = v[1] = v[2] = 0.0f;
		objStream >> v[0] >> v[1] >> v[2];
		normals.push_back(v);
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
			char slash('/');
			while (faceStrStream) {
				faceStrStream >> face[type] >> slash;
				--face[type++];

				if (FaceType_VN < type && faceStrStream) {
					return false;
				}				
			}
			objGroup.m_faces.push_back(face);
		}
		
		return true;
	}

	void ObjModelFile::loadGroup(std::istream& objStream, ObjGroup& objGroup, NameGroupMap& groupMap) {
		pushGroup(objGroup, groupMap);
		
		objGroup = ObjGroup();
		std::getline(objStream, objGroup.m_name);
		objGroup.m_name = trim(objGroup.m_name);
	}
	
	void ObjModelFile::pushGroup(const ObjGroup& objGroup, NameGroupMap& groupMap) {
		if (!objGroup.m_name.empty() && !objGroup.m_faces.empty()) {
			groupMap[objGroup.m_name] = objGroup;
		}
	}
	
} // TDZ
