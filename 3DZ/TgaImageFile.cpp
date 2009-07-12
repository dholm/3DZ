/*
 *  TgaImageFile.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdint.h>

#include <fstream>
#include <cassert>

#include "SmartPointer.hpp"
#include "TgaImageFile.hpp"

namespace TDZ {

	bool TgaImageFile::load(const std::string& path) {
		std::ifstream tgaFile(path.c_str());
		if (!tgaFile) {
			return false;
		}
		
		struct {
			uint8_t idLength;
			uint8_t colorMapType;
			uint8_t imageType;
			struct {
				uint16_t firstEntryIndex;
				uint16_t length;
				uint8_t entrySize;
			} __attribute__ ((packed)) colorMapSpecification;
			struct {
				uint16_t xOrigin;
				uint16_t yOrigin;
				uint16_t width;
				uint16_t height;
				uint8_t depth;
				uint8_t unused : 2;
				uint8_t origin : 2;
				uint8_t alphaBits : 4;
			} __attribute__ ((packed)) imageSpecification;
		} __attribute__ ((packed)) tgaFileHeader;
		
		if (!tgaFile.read(reinterpret_cast<char*>(&tgaFileHeader), sizeof(tgaFileHeader))) {
			return false;
		}
		
		setWidth(tgaFileHeader.imageSpecification.width);
		setHeight(tgaFileHeader.imageSpecification.height);
		setDepth(tgaFileHeader.imageSpecification.depth);
		
		SharedArray<uint8_t>::Type imageIdPointer(new uint8_t[tgaFileHeader.idLength]);
		if (!tgaFile.read(reinterpret_cast<char*>(imageIdPointer.get()), sizeof(tgaFileHeader.idLength))) {
			return false;
		}
		
		if (tgaFileHeader.colorMapType) {
			assert(false);
		}

		std::size_t dataSize(getWidth() * getHeight() * (getDepth() / 8));
		getDataPointer().reset(new uint8_t[dataSize]);
		if (!tgaFile.read(reinterpret_cast<char*>(getDataPointer().get()), dataSize)) {
			return false;
		}

		return true;
	}
	
	std::ostream& operator<<(std::ostream& outStream, const TgaImageFile& TgaImageFile)
	{
		outStream << "[TGA " << TgaImageFile.getWidth() << "x" << TgaImageFile.getHeight() << "x" << static_cast<int>(TgaImageFile.getDepth()) << "]";
		return outStream;
	}
	
} // TDZ
