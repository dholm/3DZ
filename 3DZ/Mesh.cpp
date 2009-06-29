/*
 *  Mesh.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <3DZ/Vector.hpp>

#include "Mesh.hpp"

namespace TDZ {

	const Mesh::Vertex Mesh::NULL_VERTEX;
	
	void Mesh::pushVertex(const Vertex& vertex) {
		m_vertices.push_back(vertex);
	}
	
	void Mesh::pushTextureVertex(const Vertex& textureVertex) {
		m_textureVertices.push_back(textureVertex);
	}
	
	void Mesh::pushNormal(const Vertex& normal) {
		m_normals.push_back(normal);
	}
	
	std::ostream& operator<<(std::ostream& outStream, const Mesh& mesh) {
		for (int i = 0; i < mesh.m_vertices.size(); ++i) {
			outStream << "[" << mesh.m_vertices[i] << ", " << mesh.m_textureVertices[i]/* << ", " << mesh.m_normals[i]*/ << "]";
		}
		return outStream;
	}
	
} // TDZ