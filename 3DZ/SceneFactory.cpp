/*
 *  SceneFactory.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-15.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "BspSceneFile.hpp"
#include "SceneFactory.hpp"

namespace TDZ {
	
	bool SceneFactory::load(const std::string& path, Scene::Pointer& outScene) {
		std::string::size_type extPos(path.rfind('.'));
		if (extPos == std::string::npos) {
			return false;
		}
		
		std::string ext(path.substr(extPos + 1));
		if (ext == "bsp") {
			outScene.reset(new BspSceneFile);
			if (!dynamic_cast<BspSceneFile*>(outScene.get())->load(path)) {
				return false;
			}
			return true;
		}
		
		return false;
	}
	
} // TDZ
