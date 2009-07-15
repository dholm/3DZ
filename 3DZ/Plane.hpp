/*
 *  Plane.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-15.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_PLANE_HPP
#define TDZ_PLANE_HPP

#include <3DZ/Mesh.hpp>

namespace TDZ {
	
	class Plane {
	public:
		Plane(const Mesh::Vertex& normal, float distance);
		
	private:
		Mesh::Vertex m_normal;
		float m_distance;
	};
	
} // TDZ

#endif /* TDZ_PLANE_HPP */
