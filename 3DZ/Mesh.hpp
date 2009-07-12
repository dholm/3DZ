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
#include <iosfwd>

namespace TDZ {

	template <std::size_t ComponentN, typename ComponentT> class Vector;

	class Mesh {
	public:
		typedef Vector<3, float> Vertex;
		typedef std::vector<Vertex> VertexVec;

		static const Vertex NULL_VERTEX;
		static const Mesh NULL_MESH;

		virtual ~Mesh() { };
		
		void pushVertex(const Vertex& vertex);
		void pushTextureVertex(const Vertex& textureVertex);
		void pushNormal(const Vertex& normal);
		
		const std::string getMaterialName() const;
		void setMaterialName(const std::string& materialName);
		
	private:
		std::string m_materialName;
		VertexVec m_vertices;
		VertexVec m_textureVertices;
		VertexVec m_normals;

		friend class FaceIterator;
		friend std::ostream& operator<<(std::ostream& outStream, const Mesh& mesh);
	};
	
	std::ostream& operator<<(std::ostream& outStream, const Mesh& mesh);
	
} // TDZ

#endif /* TDZ_MESH_HPP */
