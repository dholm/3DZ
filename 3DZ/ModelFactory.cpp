/*
 *  ModelFactory.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Vector.hpp"
#include "Image.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "ObjModelFile.hpp"
#include "ModelFactory.hpp"

namespace TDZ {
	
	bool ModelFactory::load(const std::string& path, TextureManager& textureManager, Model::Pointer& outModel) {
		std::string::size_type extPos(path.rfind('.'));
		if (extPos == std::string::npos) {
			return false;
		}
		
		std::string ext(path.substr(extPos + 1));
		if (ext == "obj") {
			outModel.reset(new ObjModelFile);
			if (!dynamic_cast<ObjModelFile*>(outModel.get())->load(path, textureManager)) {
				return false;
			}
			return true;
		}

		return false;
	}
	
} // TDZ