/*
 *  TextureManager.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-12.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <cassert>

#include "Image.hpp"
#include "ImageFactory.hpp"
#include "TextureManager.hpp"

namespace TDZ {

	TextureManager::TextureManager(const std::string& texturePath) :
		m_texturePath(texturePath),
		m_textureMap()
	{
		assert(!texturePath.empty());
	}
		
	bool TextureManager::load(const std::string& name) {
		Image::Pointer imagePointer;
		if (!ImageFactory::load(m_texturePath + "/" + name, imagePointer)) {
			return false;
		}
		m_textureMap[name] = imagePointer;
		return true;
	}
	
	void TextureManager::remove(const std::string& name) {
		if (m_textureMap.empty()) {
			return;
		}
		
		NameImageMap::iterator pos(m_textureMap.find(name));
		m_textureMap.erase(pos);
	}
	
	bool TextureManager::has(const std::string& name) const {
		if (m_textureMap.empty()) {
			return false;
		}
		
		NameImageMap::const_iterator pos(m_textureMap.find(name));
		return pos != m_textureMap.end();
	}
	
	const Image* TextureManager::get(const std::string& name) const {
		if (m_textureMap.empty()) {
			return NULL;
		}
		
		NameImageMap::const_iterator pos(m_textureMap.find(name));
		if (pos == m_textureMap.end()) {
			return NULL;
		}
		return &(*pos->second);
	}

} // TDZ
