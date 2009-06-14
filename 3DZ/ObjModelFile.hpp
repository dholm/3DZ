/*
 *  ObjModel.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_OBJMODELFILE_HPP
#define TDZ_OBJMODELFILE_HPP

#include <string>
#include <map>

#include <3DZ/Model.hpp>

/* The classes below are exported */
#pragma GCC visibility push(hidden)

namespace TDZ {
	
	class ObjModelFile : public Model {
	public:
		ObjModelFile();
		
		bool load(const std::string& path);
		
	private:
		bool loadVertex(const std::string& line);
		bool loadGroup(const std::string& line);
		bool loadFace(const std::string& line);
		
		Vector3fVec m_vertices;
		Vector3fVec m_textureVertices;
		Vector3fVec m_normals;

		struct SmoothingGroup {
			int m_id;
			FaceVec m_faces;
		};
		
		typedef std::map<int, SmoothingGroup> IdSmoothingGroupMap;
		struct Group {
			std::string m_name;
			int m_faces;
			
			IdSmoothingGroupMap m_smoothingGroups;
			int m_currentSmoothingGroupKey;
		};
		typedef std::map<std::string, Group> NameGroupMap;
		NameGroupMap m_groups;
	};
	
} // TDZ

#pragma GCC visibility pop
#endif /* TDZ_OBJMODELFILE_HPP */
