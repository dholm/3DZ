/*
 *  MeshFactory.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <3DZ/ObjMeshFile.hpp>

#include "MeshFactory.hpp"

namespace TDZ {
	
	bool MeshFactory::load(const std::string& path, Mesh& outMesh) {
		std::string::size_type extPos(path.rfind('.'));
		if (extPos == std::string::npos) {
			return false;
		}
		
		std::string ext(path.substr(extPos + 1));
		if (ext == "obj") {
			ObjMeshFile objMesh;
			if (!objMesh.load(path)) {
				return false;
			}
			outMesh = objMesh;
			return true;
		}

		return false;
	}
	
} // TDZ