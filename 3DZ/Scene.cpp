/*
 *  Scene.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-15.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Scene.hpp"

namespace TDZ {
	
	Scene::Scene() :
		m_root(new SceneNode)
	{
	}

	SceneNode::Pointer& Scene::root() {
		return m_root;
	}
	
	const SceneNode::Pointer& Scene::root() const {
		return m_root;
	}

} // TDZ
