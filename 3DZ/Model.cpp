/*
 *  Model.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-15.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <3DZ/Vector.hpp>

#include "Model.hpp"

namespace TDZ {
	
	namespace {
		static const Mesh NULL_MESH;
	}
	
	void Model::setName(const std::string& name) {
		m_name = name;
	}
	
	void Model::pushMesh(const std::string& name, const Mesh& mesh) {
		m_meshMap[name] = mesh;
	}
	
	const Mesh& Model::getMesh(const std::string& name) const {
		if (m_meshMap.empty()) {
			return NULL_MESH;
		}

		NameMeshMap::const_iterator pos(m_meshMap.find(name));
		if (pos == m_meshMap.end()) {
			return NULL_MESH;
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
