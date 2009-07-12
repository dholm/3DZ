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

	uint32_t Image::getWidth() const {
		return m_width;
	}
	
	uint32_t Image::getHeight() const {
		return m_height;
	}
	
	const uint8_t* Image::getData() const {
		return m_imageData.get();
	}
	
	void Image::setWidth(uint16_t width) {
		m_width = width;
	}
	
	void Image::setHeight(uint16_t height) {
		m_height = height;
	}
	
	uint8_t Image::getDepth() const {
		return m_depth;
	}
	
	void Image::setDepth(uint8_t depth) {
		m_depth = depth;
	}
	
	Image::ImageDataPointer& Image::getDataPointer() {
		return m_imageData;
	}

	std::ostream& operator<<(std::ostream& outStream, const Image& image)
	{
		outStream << "[Image " << image.getWidth() << "x" << image.getHeight() << "x" << static_cast<int>(image.getDepth()) << "]";
		return outStream;
	}

} // TDZ
