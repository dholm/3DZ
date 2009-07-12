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
#include <3DZ/Material.hpp>

namespace TDZ {
	
	class Model {
	public:
		typedef SharedPointer<Model>::Type Pointer;
		
		typedef std::map<std::string, Mesh> NameMeshMap;
		typedef std::map<std::string, Material> NameMaterialMap;

		virtual ~Model() { };
		
		void setName(const std::string& name);
		void pushMesh(const std::string& name, const Mesh& mesh);
		
		void pushMaterial(const Material& material);
		
		const Mesh& getMesh(const std::string& name) const;
		const Material& getMaterial(const std::string& name) const;
		
	protected:
		std::string m_name;
		NameMeshMap m_meshMap;
		NameMaterialMap m_materialMap;
		
		friend std::ostream& operator<<(std::ostream& outStream, const Model& model);
	};
	
	std::ostream& operator<<(std::ostream& outStream, const Model& model);
} // TDZ

#endif /* TDZ_MODEL_HPP */
