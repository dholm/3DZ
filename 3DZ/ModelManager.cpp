/*
 *  ModelManager.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-12.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Vector.hpp"
#include "ModelFactory.hpp"
#include "ModelManager.hpp"

namespace TDZ {
	
	ModelManager::ModelManager(const std::string& modelsPath) :
		m_modelsPath(modelsPath),
		m_modelMap()
	{
	}
		
	bool ModelManager::load(const std::string& name, TextureManager& textureManager) {
		Model::Pointer modelPointer;
		if (!ModelFactory::load(m_modelsPath + "/" + name, textureManager, modelPointer)) {
			return false;
		}
		m_modelMap[name] = modelPointer;
		return true;
	}
	
	void ModelManager::remove(const std::string& name) {
		if (m_modelMap.empty()) {
			return;
		}
		
		NameModelMap::iterator pos(m_modelMap.find(name));
		if (pos != m_modelMap.end()) {
			m_modelMap.erase(pos);
		}
	}
	
	bool ModelManager::has(const std::string& name) const {
		if (m_modelMap.empty()) {
			return false;
		}
		
		NameModelMap::const_iterator pos(m_modelMap.find(name));
		return pos != m_modelMap.end();
	}
	
	const Model* ModelManager::get(const std::string& name) const {
		if (m_modelMap.empty()) {
			return NULL;
		}
		
		NameModelMap::const_iterator pos(m_modelMap.find(name));
		if (pos == m_modelMap.end()) {
			return NULL;
		}
		return pos->second.get();
	}
	
} // TDZ
