/*
 *  Mesh.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_MESH_HPP
#define TDZ_MESH_HPP

#include <vector>

#include <3DZ/Vector.hpp>

/* The classes below are exported */
#pragma GCC visibility push(default)

namespace TDZ {

	class Mesh {
	public:
		typedef Vector<3, float> Vertex;

		virtual ~Mesh() { };
		
	protected:
		typedef std::vector<Vertex> VertexVec;
		typedef Vector<3, int> Face;
		typedef std::vector<Face> FaceVec;
		
		VertexVec m_vertices;
		VertexVec m_textureVertices;
		VertexVec m_normals;

		FaceVec m_faces;
		
		friend class FaceIterator;
	};
	
} // TDZ

#pragma GCC visibility pop
#endif /* TDZ_MESH_HPP */
