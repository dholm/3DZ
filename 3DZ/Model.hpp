/*
 *  Model.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_MODEL_HPP
#define TDZ_MODEL_HPP

#include <vector>

#include <3DZ/Vector.hpp>

/* The classes below are exported */
#pragma GCC visibility push(default)

namespace TDZ {

	class Model {
	public:
		typedef Vector<3, float> Vector3f;
		
		virtual ~Model() { };
		
	protected:
		typedef std::vector<Vector3f> Vector3fVec;
		
		Vector3fVec m_vertices;
		Vector3fVec m_textureVertices;
		Vector3fVec m_normals;

		struct Face {
			int m_vertexIndex;
			int m_textureVertexIndex;
			int m_normalIndex;
		};
		typedef std::vector<Face> FaceVec;
		FaceVec m_faces;
	};
	
} // TDZ

#pragma GCC visibility pop
#endif /* TDZ_MODEL_HPP */
