/*
 *  Material.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Vector.hpp"
#include "Material.hpp"

namespace TDZ {
	
	const Material Material::NULL_MATERIAL;
	
	void Material::setName(const std::string& name) {
		m_name = name;
	}
	
	const std::string& Material::getName() const {
		return m_name;
	}
	
	void Material::setTextureName(const std::string& textureName) {
		m_textureName = textureName;
	}
	
	const std::string& Material::getTextureName() const {
		return m_textureName;
	}

} // TDZ

