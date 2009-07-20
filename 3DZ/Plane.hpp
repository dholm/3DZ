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

#include <3DZ/Vector.hpp>

namespace TDZ {
	
	template <typename ComponentT>
	class Plane {
	public:
		Plane() :
			m_normal(Vector3<ComponentT>(0, 0, 1)),
			m_distance(ComponentT(0))
		{
		}
		
		Plane(const Vector<3, ComponentT>& normal, ComponentT distance) :
			m_normal(normal),
			m_distance(distance)
		{
		}
		
		Plane(const Vector<3, ComponentT>& normal, const Vector<3, ComponentT>& point) :
			m_normal(normal),
			m_distance(normal.dot(point))
		{
		}
		
		const Vector<3, ComponentT>& normal() const {
			return m_normal;
		}
		
		const ComponentT& distance() const {
			return m_distance;
		}
		
		Plane<ComponentT> normalized() const {
			ComponentT m = ComponentT(1) / m_normal.length();
			return Plane<ComponentT>(Vector3<ComponentT>(m_normal[0] * m, m_normal[1] * m, m_normal[2] * m), m_distance * m);
		}
		
	private:
		Vector<3, ComponentT> m_normal;
		ComponentT m_distance;
	};
	
} // TDZ

#endif /* TDZ_PLANE_HPP */
