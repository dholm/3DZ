/*
 *  Model.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-15.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Model.hpp"

namespace TDZ {
	
	void Model::setName(const std::string& name) {
		m_name = name;
	}
	
	void Model::pushMesh(const std::string& name, const Mesh& mesh) {
		m_meshMap[name] = mesh;
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
