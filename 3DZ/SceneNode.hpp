/*
 *  SceneNode.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-16.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_SCENENODE_HPP
#define TDZ_SCENENODE_HPP

#include <vector>

#include <3DZ/SmartPointer.hpp>

namespace TDZ {

	class SceneNode {
	public:
		typedef SharedPointer<SceneNode>::Type Pointer;
		
		SceneNode();
		SceneNode(const Pointer& parent);
		virtual ~SceneNode() { }
		
		virtual void pushChild(const Pointer& child);
		
	private:
		typedef std::vector<Pointer> PointerVector;

		Pointer m_parent;
		PointerVector m_children;
	};
	
} // TDZ
#endif /* TDZ_SCENENODE_HPP */
