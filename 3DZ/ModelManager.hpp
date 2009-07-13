/*
 *  ModelManager.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-12.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_MODELMANAGER_HPP
#define TDZ_MODELMANAGER_HPP

#include <string>
#include <map>

#include <3DZ/TextureManager.hpp>
#include <3DZ/Model.hpp>

namespace TDZ {

	class ModelManager {
	public:
		ModelManager(const std::string& modelsPath);
		
		bool load(const std::string& name, TextureManager& textureManager);
		void remove(const std::string& name);
		bool has(const std::string& name) const;
		const Model* get(const std::string& name) const;
		
	private:
		typedef std::map<std::string, Model::Pointer> NameModelMap;
		
		std::string m_modelsPath;
		NameModelMap m_modelMap;
	};
	
} // TDZ

#endif /* TDZ_MODELMANAGER_HPP */
