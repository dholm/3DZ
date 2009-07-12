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
#include <vector>
#include <map>

#include <3DZ/Model.hpp>

namespace TDZ {
	
	class Mesh;
	class TextureManager;
	
	class ObjModelFile : public Model {
	public:
		bool load(const std::string& path, TextureManager& textureManager);

	private:
		operator Model() const;

		enum FaceType {
			FaceType_V = 0,
			FaceType_VT,
			FaceType_VN,
		};
		typedef Vector<3, int> Face;
		typedef std::vector<Face> FaceVec;

		struct ObjGroup {
			std::string m_name;
			std::string m_materialName;
			FaceVec m_faces;
		};
		typedef std::map<std::string, ObjGroup> NameGroupMap;

		void loadVertex(std::istream& objStream, Mesh::VertexVec& vertices);
		void loadTextureVertex(std::istream& objStream, Mesh::VertexVec& textureVertices);
		void loadNormal(std::istream& objStream, Mesh::VertexVec& normals);
		bool loadFace(std::istream& objStream, ObjGroup& objGroup) const;
		void loadGroup(std::istream& objStream, ObjGroup& objGroup, NameGroupMap& groupMap);
		bool loadMaterial(std::istream& inStream, const std::string& basePath);

		void pushGroup(const ObjGroup& objGroup, NameGroupMap& groupMap);
	};
	
} // TDZ

#endif /* TDZ_OBJMODELFILE_HPP */
