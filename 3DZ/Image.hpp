/*
 *  Image.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_IMAGE_HPP
#define TDZ_IMAGE_HPP

#include <iosfwd>

#include <3DZ/SmartPointer.hpp>

namespace TDZ {
	
	class Image {
	public:
		typedef SharedPointer<Image>::Type Pointer;
		
		virtual ~Image() { };
		
		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;
		virtual uint8_t getDepth() const = 0;
		virtual const uint8_t* getData() const = 0;
	};
	
	std::ostream& operator<<(std::ostream& outStream, const Image& image);

} // TDZ

#endif /* TDZ_IMAGE_HPP */
