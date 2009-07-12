/*
 *  TextureManager.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-12.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_TEXTUREMANAGER_HPP
#define TDZ_TEXTUREMANAGER_HPP

#include <map>
#include <string>

namespace TDZ {

	class Image;
	class TextureManager {
	public:
		TextureManager(const std::string& texturePath);
		
		bool load(const std::string& name);
		void remove(const std::string& name);
		bool has(const std::string& name) const;
		const Image* get(const std::string& name) const;
		
	private:
		typedef std::map<std::string, Image> NameImageMap;
		
		std::string m_texturePath;
		NameImageMap m_textureMap;
	};
	
} // TDZ

#endif /* TDZ_TEXTUREMANAGER_HPP */
