/*
 *  Image.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Image.hpp"

namespace TDZ {

	std::ostream& operator<<(std::ostream& outStream, const Image& image)
	{
		outStream << "[Image " << image.getWidth() << "x" << image.getHeight() << "x" << static_cast<int>(image.getDepth()) << "]";
		return outStream;
	}

} // TDZ
