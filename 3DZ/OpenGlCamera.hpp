/*
 *  OpenGlCamera.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-18.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_OPENGLCAMERA_HPP
#define TDZ_OPENGLCAMERA_HPP

#include <3DZ/Camera.hpp>

namespace TDZ {
	
	class OpenGlCamera : public Camera {
	public:
		void render() const;
	};
	
} // TDZ

#endif /* TDZ_OPENGLCAMERA_HPP */
