/*
 *  ObjModelFile.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_OBJMODELFILE_HPP
#define TDZ_OBJMODELFILE_HPP

#include <iosfwd>
#include <string>

#include <3DZ/Model.hpp>

namespace TDZ {
	
	class ObjModelFile {
	public:
		ObjModelFile();
		
		operator Model() const;
		bool load(const std::string& path);

	private:
		enum FaceType {
			FaceType_V = 0,
			FaceType_VT,
			FaceType_VN,
		};
		typedef Vector<3, int> Face;
		typedef std::vector<Face> FaceVec;

		struct ObjGroup {
			std::string m_name;
			FaceVec m_faces;
			Mesh::VertexVec m_vertices;
			Mesh::VertexVec m_textureVertices;
			Mesh::VertexVec m_normals;
		};
		typedef std::map<std::string, ObjGroup> NameGroupMap;

		void loadVertex(std::istream& objStream, ObjGroup& objGroup) const;
		void loadTextureVertex(std::istream& objStream, ObjGroup& objGroup) const;
		void loadNormal(std::istream& objStream, ObjGroup& objGroup) const;
		bool loadFace(std::istream& objStream, ObjGroup& objGroup) const;
		void loadGroup(std::istream& objStream, ObjGroup& objGroup);

		void pushGroup(const ObjGroup& objGroup);
		void groupToMesh(const ObjGroup& group, Mesh& outMesh) const;
		
		std::string m_name;
		NameGroupMap m_groupMap;
	};
	
} // TDZ

#endif /* TDZ_OBJMODELFILE_HPP */
