/*
 *  SceneFactory.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-15.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_SCENEFACTORY_HPP
#define TDZ_SCENEFACTORY_HPP

#include <3DZ/Scene.hpp>

namespace TDZ {
	
	class SceneFactory {
	public:
		static bool load(const std::string& path, Scene::Pointer& outScene);
	};
	
} // TDZ

#endif /* TDZ_SCENEFACTORY_HPP */
