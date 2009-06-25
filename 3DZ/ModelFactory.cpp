/*
 *  ModelFactory.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <3DZ/ObjModelFile.hpp>

#include "ModelFactory.hpp"

namespace TDZ {
	
	bool ModelFactory::load(const std::string& path, Model& outModel) {
		std::string::size_type extPos(path.rfind('.'));
		if (extPos == std::string::npos) {
			return false;
		}
		
		std::string ext(path.substr(extPos + 1));
		if (ext == "obj") {
			ObjModelFile objModel;
			if (!objModel.load(path)) {
				return false;
			}
			outModel = objModel;
			return true;
		}

		return false;
	}
	
} // TDZ