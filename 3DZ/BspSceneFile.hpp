/*
 *  BspSceneFile.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-15.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_BSPSCENEFILE_HPP
#define TDZ_BSPSCENEFILE_HPP

#include <vector>

#include <3DZ/Mesh.hpp>
#include <3DZ/Plane.hpp>
#include <3DZ/Scene.hpp>

namespace TDZ {
	
	class BspSceneFile : public Scene {
	public:
		bool load(const std::string& path);
		
	private:
		struct BspDirEntry {
			int32_t offset;
			int32_t length;
		} __attribute__ ((packed));
		
		bool loadBspDirEntry(std::istream& bspStream, const BspDirEntry& entry, SharedArray<uint8_t>::Type& outData);
		bool loadTextures(std::istream& bspStream, const BspDirEntry& texturesEntry);
		bool loadPlanes(std::istream& bspStream, const BspDirEntry& planesEntry);
		bool loadNodes(std::istream& bspStream, const BspDirEntry& nodesEntry);
		bool loadLeaves(std::istream& bspStream, const BspDirEntry& leafsEntry);
		bool loadLeafFaces(std::istream& bspStream, const BspDirEntry& leafFacesEntry);
		bool loadModels(std::istream& bspStream, const BspDirEntry& modelsEntry);
		bool loadVertices(std::istream& bspStream, const BspDirEntry& verticesEntry);
		bool loadFaces(std::istream& bspStream, const BspDirEntry& facesEntry);
		
		std::vector<Plane> m_planes;
		std::vector<Mesh::Vertex> m_vertices;
		std::vector<Mesh::Vertex> m_normals;
	};
	
} // TDZ

#endif /* TDZ_BSPSCENEFILE_HPP */
