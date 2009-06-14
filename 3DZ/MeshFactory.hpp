/*
 *  MeshFactory.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_MESHFACTORY_HPP
#define TDZ_MESHFACTORY_HPP

#include <3DZ/Mesh.hpp>

/* The classes below are exported */
#pragma GCC visibility push(default)

namespace TDZ {

	class MeshFactory {
	public:
		static bool load(const std::string& path, Mesh& outMesh);
	};
	
} // TDZ

#pragma GCC visibility pop
#endif /* TDZ_MESHFACTORY_HPP */
