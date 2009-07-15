/*
 *  MtlMaterialFile.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_MTLMATERIALFILE_HPP
#define TDZ_MTLMATERIALFILE_HPP

#include <3DZ/Model.hpp>
#include <3DZ/Material.hpp>
#include <3DZ/TextureManager.hpp>

namespace TDZ {
	
	class MtlMaterialFile {
	public:
		bool load(const std::string& path, TextureManager& textureManager, Model& outModel);
	};
	
} // TDZ

#endif /* TDZ_MTLMATERIALFILE_HPP */
