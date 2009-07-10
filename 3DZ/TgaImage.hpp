/*
 *  TgaImage.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_TGAIMAGE_HPP
#define TDZ_TGAIMAGE_HPP

#include <3DZ/Image.hpp>
#include <3DZ/SmartPointer.hpp>

namespace TDZ {

	class TgaImage : public Image {
	public:
		virtual ~TgaImage() { };
		
		bool load(const std::string& path);
		
		uint32_t getWidth() const;
		uint32_t getHeight() const;
		const uint8_t* getData() const;
		
	private:
		uint16_t m_width;
		uint16_t m_height;
		uint8_t	m_depth;
		SharedArray<uint8_t>::Type m_imageData;
		
		friend std::ostream& operator<<(std::ostream& outStream, const TgaImage& tgaImage);
	};

} // TDZ

#endif /* TDZ_TGAIMAGE_HPP */
