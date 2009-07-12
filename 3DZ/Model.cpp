/*
 *  Model.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-15.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Vector.hpp"
#include "Image.hpp"
#include "Model.hpp"

namespace TDZ {
	
	void Model::setName(const std::string& name) {
		m_name = name;
	}
	
	void Model::pushMesh(const std::string& name, const Mesh& mesh) {
		m_meshMap[name] = mesh;
	}
	
	void Model::pushMaterial(const Material& material) {
		m_materialMap[material.getName()] = material;
	}

	const Mesh& Model::getMesh(const std::string& name) const {
		if (m_meshMap.empty()) {
			return Mesh::NULL_MESH;
		}

		NameMeshMap::const_iterator pos(m_meshMap.find(name));
		if (pos == m_meshMap.end()) {
			return Mesh::NULL_MESH;
		}
		return pos->second;
	}
	
	const Material& Model::getMaterial(const std::string& name) const {
		if (m_materialMap.empty()) {
			return Material::NULL_MATERIAL;
		}
		
		NameMaterialMap::const_iterator pos(m_materialMap.find(name));
		if (pos == m_materialMap.end()) {
			return Material::NULL_MATERIAL;
		}
		return pos->second;
	}

	std::ostream& operator<<(std::ostream& outStream, const Model& model)
	{
		outStream << "Model: " << model.m_name;
		
		for (Model::NameMeshMap::const_iterator it(model.m_meshMap.begin()); it != model.m_meshMap.end(); ++it) {
			outStream << std::endl << "Mesh: " << it->first << std::endl;
			outStream << it->second;
		}

		return outStream;
	}
	
} // TDZ
