/*
 *  Frustum.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-19.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 * References:
 *  http://www.dhpoware.com/demos/glCamera3.html
 *  http://oss.sgi.com/cgi-bin/cvsweb.cgi/projects/ogl-sample/main/gfx/lib/glu/libutil/project.c
 */

#ifndef TDZ_FRUSTUM_HPP
#define TDZ_FRUSTUM_HPP

#include <3DZ/Radian.hpp>
#include <3DZ/Plane.hpp>
#include <3DZ/Vector.hpp>

namespace TDZ {

	template <typename ComponentT>
	class Frustum {
	public:
		enum Clip {
			Clip_Bottom,
			Clip_Top,
			Clip_Left,
			Clip_Right,
			Clip_Near,
			Clip_Far
		};
		
		Frustum(Radian<ComponentT> fovY, ComponentT aspect, ComponentT near, ComponentT far) :
			m_fovY(fovY),
			m_aspect(aspect),
			m_near(near),
			m_far(far),
			m_planes()
		{
			updatePlanes();
		}
		
		operator Matrix<4, 4, ComponentT>() const {
			ComponentT aspectInv = ComponentT(1) / m_aspect;
			ComponentT xScale = ComponentT(1) / tan(m_fovY / ComponentT(2));
			ComponentT yScale = xScale / aspectInv;
			
			Matrix<4, 4, ComponentT> result(IdentityMatrix<4, float>::create());
			result(0, 0) = xScale;
			result(1, 1) = yScale;
			result(2, 2) = (m_far + m_near) / (m_near - m_far);
			result(2, 3) = -ComponentT(1);
			result(3, 2) = (ComponentT(2) * m_far * m_near) / (m_near - m_far);
			return result;
		}
		
	private:
		void updatePlanes() {
			ComponentT height = tan(m_fovY / 2.0);
			ComponentT width = height * m_aspect;
			
			Vector<3, ComponentT> normals[4];
			normals[Clip_Bottom] = Vector3<ComponentT>(0, 1, -height);
			normals[Clip_Top] = Vector3<ComponentT>(0, -1, -height);
			normals[Clip_Left] = Vector3<ComponentT>(1, 0, -width);
			normals[Clip_Right] = Vector3<ComponentT>(-1, 0, -width);
			for (int i = 0; i < 4; ++i) {
				normals[i] = normals[i].normalized();
				m_planes[i] = Plane<ComponentT>(normals[i], Vector3<ComponentT>(0, 0, 0));
			}
			
			m_planes[Clip_Near] = Plane<ComponentT>(Vector3<ComponentT>(0, 0, -1), -m_near);
			m_planes[Clip_Far] = Plane<ComponentT>(Vector3<ComponentT>(0, 0, 1), m_far);
		}
		
		Radian<ComponentT> m_fovY;
		ComponentT m_aspect;
		ComponentT m_near;
		ComponentT m_far;
	
		Plane<ComponentT> m_planes[6];
	};
	
} // TDZ

#endif /* TDZ_FRUSTUM_HPP */
