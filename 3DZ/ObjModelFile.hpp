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

#include <3DZ/Mesh.hpp>

/* The classes below are exported */
#pragma GCC visibility push(hidden)

namespace TDZ {
	
	class ObjModelFile : public Mesh {
	public:
		ObjModelFile();
		
		bool load(const std::string& path);
		
	private:
		bool loadVertex(std::istream& objStream);
		bool loadTextureVertex(std::istream& objStream);
		bool loadNormal(std::istream& objStream);
		bool loadGroup(std::istream& objStream);
		bool loadFace(std::istream& objStream);
		
		std::string m_name;
	};
	
} // TDZ

#pragma GCC visibility pop
#endif /* TDZ_OBJMODELFILE_HPP */
