/*
 *  OpenGlCamera.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-18.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <OpenGL/gl.h>

#include "OpenGlCamera.hpp"

namespace TDZ {
	
	void OpenGlCamera::render() const {
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(view().transposed());
	}
	
} // TDZ
