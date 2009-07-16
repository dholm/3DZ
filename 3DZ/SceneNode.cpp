/*
 *  SceneNode.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-16.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "SceneNode.hpp"

namespace TDZ {
	
	SceneNode::SceneNode() :
		m_parent(),
		m_children()
	{
	}

	SceneNode::SceneNode(const Pointer& parent) :
		m_parent(parent),
		m_children()
	{
	}

	void SceneNode::pushChild(const Pointer& child) {
		m_children.push_back(child);
	}
	
} // TDZ
