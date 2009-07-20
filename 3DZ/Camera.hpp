/*
 *  Camera.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-18.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_CAMERA_HPP
#define TDZ_CAMERA_HPP

#include <3DZ/SmartPointer.hpp>
#include <3DZ/Vector.hpp>
#include <3DZ/Matrix.hpp>
#include <3DZ/Quaternion.hpp>
#include <3DZ/Frustum.hpp>

namespace TDZ {
	
	class Camera {
	public:
		typedef SharedPointer<Camera>::Type Pointer;
		
		Camera();
		virtual ~Camera() { }
		
		virtual void setProjection(const Frustum<float>& projection);
		virtual void setPosition(const Vector<3, float>& pos);
		virtual void setOrientation(const Quaternion<float>& o);
		virtual void setTarget(const Vector<3, float>& target);
		virtual void render() const = 0;
		
	protected:
		const Matrix<4, 4, float>& projection() const;
		const Matrix<4, 4, float>& view() const;
		
	private:
		void updateViewMatrix();
		
		Vector<3, float> m_eye;
		Vector<3, float> m_xAxis;
		Vector<3, float> m_yAxis;
		Vector<3, float> m_zAxis;
		Quaternion<float> m_orientation;
		
		Matrix<4, 4, float> m_projection;
		Matrix<4, 4, float> m_view;
	};
	
} // TDZ

#endif /* TDZ_CAMERA_HPP */
