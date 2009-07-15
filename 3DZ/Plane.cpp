/*
 *  Plane.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-15.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Plane.hpp"

namespace TDZ {
	
	Plane::Plane(const Mesh::Vertex& normal, float distance) :
		m_normal(normal),
		m_distance(distance)
	{
	}
	
} // TDZ
