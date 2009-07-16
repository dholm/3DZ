/*
 *  Scene.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-15.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_SCENE_HPP
#define TDZ_SCENE_HPP

#include <3DZ/SmartPointer.hpp>
#include <3DZ/SceneNode.hpp>

namespace TDZ {
	
	class Scene {
	public:
		typedef SharedPointer<Scene>::Type Pointer;
		
		Scene();
		virtual ~Scene() { }
		
		SceneNode::Pointer& root();
		const SceneNode::Pointer& root() const;
		
	private:
		SceneNode::Pointer m_root;
	};
	
} // TDZ

#endif /* TDZ_SCENE_HPP */
