/*
 *  TgaImageFile.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_TgaImageFile_HPP
#define TDZ_TgaImageFile_HPP

#include <3DZ/Image.hpp>
#include <3DZ/SmartPointer.hpp>

namespace TDZ {

	class TgaImageFile : public Image {
	public:		
		virtual ~TgaImageFile() { };
		
		bool load(const std::string& path);
				
		friend std::ostream& operator<<(std::ostream& outStream, const TgaImageFile& TgaImageFile);
	};

} // TDZ

#endif /* TDZ_TgaImageFile_HPP */
