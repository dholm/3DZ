/*
 *  ModelFactory.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_MODELFACTORY_HPP
#define TDZ_MODELFACTORY_HPP

#include <3DZ/Model.hpp>

namespace TDZ {

	class TextureManager;
	class ModelFactory {
	public:
		static bool load(const std::string& path, TextureManager& textureManager, Model::Pointer& outModel);
	
	private:
		ModelFactory() { };
	};
	
} // TDZ

#endif /* TDZ_MODELFACTORY_HPP */
