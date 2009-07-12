/*
 *  Mesh.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Vector.hpp"
#include "Image.hpp"
#include "Material.hpp"
#include "Mesh.hpp"

namespace TDZ {

	const Mesh::Vertex Mesh::NULL_VERTEX;
	const Mesh Mesh::NULL_MESH;
	
	void Mesh::pushVertex(const Vertex& vertex) {
		m_vertices.push_back(vertex);
	}
	
	void Mesh::pushTextureVertex(const Vertex& textureVertex) {
		m_textureVertices.push_back(textureVertex);
	}
	
	void Mesh::pushNormal(const Vertex& normal) {
		m_normals.push_back(normal);
	}
	
	const std::string Mesh::getMaterialName() const {
		return m_materialName;
	}
	
	void Mesh::setMaterialName(const std::string& materialName) {
		m_materialName = materialName;
	}

	std::ostream& operator<<(std::ostream& outStream, const Mesh& mesh) {
		for (int i = 0; i < mesh.m_vertices.size(); ++i) {
			outStream << "[" << mesh.m_vertices[i] << ", " << mesh.m_textureVertices[i]/* << ", " << mesh.m_normals[i]*/ << "]";
		}
		return outStream;
	}
	
} // TDZ