/*
 *  Material.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_MATERIAL_HPP
#define TDZ_MATERIAL_HPP

#include <3DZ/SmartPointer.hpp>

namespace TDZ {

	template <std::size_t N, typename ComponentT> class Vector;
	class Image;

	class Material {
	public:
		typedef Vector<3, float> Color;
		
		static const Material NULL_MATERIAL;
		
		virtual ~Material() { }
		
		void setName(const std::string& name);
		const std::string& getName() const;
		
		void setTextureName(const std::string& textureName);
		const std::string& getTextureName() const;
		
	private:
		std::string m_name;
		float m_refractionIndex;
		std::string m_textureName;
	};
	
} // TDZ

#endif /* TDZ_MATERIAL_HPP */
