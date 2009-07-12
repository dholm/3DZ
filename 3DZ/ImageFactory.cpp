/*
 *  ImageFactory.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "TgaImageFile.hpp"
#include "ImageFactory.hpp"

namespace TDZ {
	
	bool ImageFactory::load(const std::string& path, Image::Pointer& outImage) {
		std::string::size_type extPos(path.rfind('.'));
		if (extPos == std::string::npos) {
			return false;
		}
		
		std::string ext(path.substr(extPos + 1));
		if (ext == "tga") {
			outImage.reset(new TgaImageFile);
			if (!dynamic_cast<TgaImageFile*>(outImage.get())->load(path)) {
				return false;
			}
			return true;
		}
		
		return false;
	}
	
} // TDZ
