/*
 *  MtlMaterialFile.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <map>

#include "StringUtils.hpp"
#include "Vector.hpp"
#include "TextureManager.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "Material.hpp"
#include "ImageFactory.hpp"
#include "MtlMaterialFile.hpp"

namespace TDZ {
	
	bool MtlMaterialFile::load(const std::string& path, TextureManager& textureManager, Model& outModel) {
		std::ifstream mtlFile(path.c_str());
		if (!mtlFile) {
			return false;
		}

		Material currentMaterial;
		std::string word;
		for (std::string word; mtlFile >> word; word.clear()) {
			if (word == "newmtl") {
				if (!(mtlFile >> word)) {
					return false;
				}

				if (!currentMaterial.getName().empty()) {
					outModel.pushMaterial(currentMaterial);
				}
				currentMaterial = Material();
				currentMaterial.setName(trim(word));
			} else if (word == "map_Kd") {
				if (!(mtlFile >> word)) {
					return false;
				}
				if (!textureManager.load(trim(word))) {
					return false;
				}
				currentMaterial.setTextureName(trim(word));
			} else {
				/* Skip */
			}
		}

		if (!currentMaterial.getName().empty()) {
			outModel.pushMaterial(currentMaterial);
		}
		
		return true;
	}
	
} // TDZ
