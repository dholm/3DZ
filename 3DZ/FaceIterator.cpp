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
		m_faceIt(m_meshRef.m_faces.begin())
	{
	}
	
	bool FaceIterator::done() const {
		return m_faceIt == m_meshRef.m_faces.end();
	}
	
	FaceIterator& FaceIterator::operator++() {
		++m_faceIt;
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
		return m_meshRef.m_vertices[(*m_faceIt)[0]];
	}
	
	const Mesh::Vertex& FaceIterator::textureVertex() const {
		return m_meshRef.m_vertices[(*m_faceIt)[1]];
	}
	
	const Mesh::Vertex& FaceIterator::normal() const {
		return m_meshRef.m_vertices[(*m_faceIt)[2]];
	}
	
} // TDZ
