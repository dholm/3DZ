/*
 *  Camera.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-19.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Camera.hpp"

namespace TDZ {

	Camera::Camera() :
		m_eye(Vector3<float>(0.0, 0.0, 0.0)),
		m_xAxis(Vector3<float>(1.0, 0.0, 0.0)),
		m_yAxis(Vector3<float>(0.0, 1.0, 0.0)),
		m_zAxis(Vector3<float>(0.0, 0.0, 1.0)),
		m_orientation(IdentityQuaternion<float>::create()),
		m_projection(IdentityMatrix<4, float>::create()),
		m_view(IdentityMatrix<4, float>::create())
	{
	}
	
	Vector<3, float> Camera::getForward() const {
		return cross(Vector3<float>(0.0, 1.0, 0.0), m_xAxis).normalized();
	}
	
	Quaternion<float> Camera::getOrientation() const {
		return m_orientation;
	}

	void Camera::setProjection(const Frustum<float>& projection) {
		m_projection = projection;
	}

	void Camera::setPosition(const Vector<3, float>& pos) {
		m_eye = pos;
		updateViewMatrix();
	}
	
	void Camera::setOrientation(const Quaternion<float>& o) {
		m_orientation = o;
		updateViewMatrix();
	}
	
	void Camera::setTarget(const Vector<3, float>& target) {
		m_zAxis = (m_eye - target).normalized();
		m_xAxis = cross(m_yAxis, m_zAxis).normalized();
		m_yAxis = cross(m_zAxis, m_xAxis).normalized();
		
		m_view(0, 0) = m_xAxis[0];
		m_view(1, 0) = m_xAxis[1];
		m_view(2, 0) = m_xAxis[2];
		m_view(3, 0) = -m_xAxis.dot(m_eye);
		
		m_view(0, 1) = m_yAxis[0];
		m_view(1, 1) = m_yAxis[1];
		m_view(2, 1) = m_yAxis[2];
		m_view(3, 1) = -m_yAxis.dot(m_eye);
		
		m_view(0, 2) = m_zAxis[0];
		m_view(1, 2) = m_zAxis[1];
		m_view(2, 2) = m_zAxis[2];
		m_view(3, 2) = -m_zAxis.dot(m_eye);
		
		m_orientation = m_view;
	}
	
	const Matrix<4, 4, float>& Camera::projection() const {
		return m_projection;
	}
	
	const Matrix<4, 4, float>& Camera::view() const {
		return m_view;
	}
	
	void Camera::updateViewMatrix() {
		m_view = m_orientation;
		m_xAxis = Vector3<float>(m_view(0, 0), m_view(1, 0), m_view(2, 0));
		m_yAxis = Vector3<float>(m_view(0, 1), m_view(1, 1), m_view(2, 1));
		m_zAxis = Vector3<float>(m_view(0, 2), m_view(1, 2), m_view(2, 2));
		
		m_view(3, 0) = -m_xAxis.dot(m_eye);
		m_view(3, 1) = -m_yAxis.dot(m_eye);
		m_view(3, 2) = -m_zAxis.dot(m_eye);
	}
	
} // TDZ
