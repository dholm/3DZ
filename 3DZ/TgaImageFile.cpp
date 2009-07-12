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
		
		m_width = tgaFileHeader.imageSpecification.width;
		m_height = tgaFileHeader.imageSpecification.height;
		m_depth = tgaFileHeader.imageSpecification.depth;
		
		SharedArray<uint8_t>::Type imageIdPointer(new uint8_t[tgaFileHeader.idLength]);
		if (!tgaFile.read(reinterpret_cast<char*>(imageIdPointer.get()), sizeof(tgaFileHeader.idLength))) {
			return false;
		}
		
		if (tgaFileHeader.colorMapType) {
			assert(false);
		}

		std::size_t dataSize(m_width * m_height * (m_depth / 8));
		m_imageData.reset(new uint8_t[dataSize]);
		if (!tgaFile.read(reinterpret_cast<char*>(m_imageData.get()), dataSize)) {
			return false;
		}

		return true;
	}
	
	uint32_t TgaImageFile::getWidth() const {
		return m_width;
	}
	
	uint32_t TgaImageFile::getHeight() const {
		return m_height;
	}
	
	uint8_t TgaImageFile::getDepth() const {
		return m_depth;
	}
	
	const uint8_t* TgaImageFile::getData() const {
		return m_imageData.get();
	}
	
	std::ostream& operator<<(std::ostream& outStream, const TgaImageFile& TgaImageFile)
	{
		outStream << "[TGA " << TgaImageFile.getWidth() << "x" << TgaImageFile.getHeight() << "x" << static_cast<int>(TgaImageFile.getDepth()) << "]";
		return outStream;
	}
	
} // TDZ
