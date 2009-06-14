/*
 *  FaceIterator.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <3DZ/Mesh.hpp>

namespace TDZ {

	class FaceIterator {
	public:
		FaceIterator(const Mesh& meshRef);
		
		FaceIterator& operator++();
		const FaceIterator& operator++() const;

		const FaceIterator& operator*() const;
		const FaceIterator* operator->() const;
		
		bool done() const;
		
		const Mesh::Vertex& vertex() const;
		const Mesh::Vertex& textureVertex() const;
		const Mesh::Vertex& normal() const;
				
	private:
		const Mesh& m_meshRef;
		Mesh::FaceVec::const_iterator m_faceIt;
	};
	
} // TDZ
