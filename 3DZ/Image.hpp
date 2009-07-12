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
		virtual ~Image() { };
		
		virtual uint32_t getWidth() const;
		virtual uint32_t getHeight() const;
		virtual uint8_t getDepth() const;
		virtual const uint8_t* getData() const;
		
	protected:
		typedef SharedArray<uint8_t>::Type ImageDataPointer;
		
		void setWidth(uint16_t width);
		void setHeight(uint16_t height);
		void setDepth(uint8_t depth);
		
		ImageDataPointer& getDataPointer();
		
	private:
		uint16_t m_width;
		uint16_t m_height;
		uint8_t	m_depth;
		ImageDataPointer m_imageData;
	};
	
	std::ostream& operator<<(std::ostream& outStream, const Image& image);

} // TDZ

#endif /* TDZ_IMAGE_HPP */
