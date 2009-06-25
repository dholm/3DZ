/*
 *  FaceIterator.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "FaceIterator.hpp"

namespace TDZ {

	FaceIterator::FaceIterator(const Mesh& meshRef) :
		m_meshRef(meshRef),
		m_currentVertex(0)
	{
	}
	
	bool FaceIterator::done() const {
		return m_meshRef.m_vertices.size() <= m_currentVertex;
	}
	
	FaceIterator& FaceIterator::operator++() {
		++m_currentVertex;
		return *this;
	}
	
	const FaceIterator& FaceIterator::operator++() const {
		++(*this);
		return *this;
	}

	const FaceIterator& FaceIterator::operator*() const {
		return *this;
	}
	
	const FaceIterator* FaceIterator::operator->() const {
		return this;
	}

	const Mesh::Vertex& FaceIterator::vertex() const {
		if (m_currentVertex < m_meshRef.m_vertices.size()) {
			return m_meshRef.m_vertices[m_currentVertex];
		}
		return Mesh::NULL_VERTEX;
	}
	
	const Mesh::Vertex& FaceIterator::textureVertex() const {
		if (m_currentVertex < m_meshRef.m_textureVertices.size()) {
			return m_meshRef.m_textureVertices[m_currentVertex];
		}
		return Mesh::NULL_VERTEX;
	}
	
	const Mesh::Vertex& FaceIterator::normal() const {
		if (m_currentVertex < m_meshRef.m_normals.size()) {
			return m_meshRef.m_normals[m_currentVertex];
		}
		return Mesh::NULL_VERTEX;
	}
	
} // TDZ
