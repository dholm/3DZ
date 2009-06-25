/*
 *  Model.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-15.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_MODEL_HPP
#define TDZ_MODEL_HPP

#include <string>
#include <map>
#include <iosfwd>

#include <3DZ/Mesh.hpp>

namespace TDZ {
	
	class Model {
	public:
		typedef std::map<std::string, Mesh> NameMeshMap;

		void setName(const std::string& name);
		void pushMesh(const std::string& name, const Mesh& mesh);
		
	protected:
		std::string	m_name;
		NameMeshMap m_meshMap;
		
		friend std::ostream& operator<<(std::ostream& outStream, const Model& model);
	};
	
	std::ostream& operator<<(std::ostream& outStream, const Model& model);
} // TDZ

#endif /* TDZ_MODEL_HPP */
