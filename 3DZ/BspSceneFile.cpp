/*
 *  BspSceneFile.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-15.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <fstream>
#include <vector>

#include "SmartPointer.hpp"
#include "BspSceneFile.hpp"

namespace TDZ {
	
	namespace {
		const std::string BSP_HEADER_MAGIC("IBSP");
	}
	
	namespace Q3Bsp {
		const uint8_t BSP_QUAKE3_VERSION(0x2e);
		
		enum {
			DirEntry_Entities,		/**< Game-reated object descriptions */
			DirEntry_Textures,		/**< Surface descriptions */
			DirEntry_Planes,		/**< Planes used by map geometry */
			DirEntry_Nodes,			/**< BSP tree nodes */
			DirEntry_Leaves,			/**< BSP tree leaves */
			DirEntry_Leaffaces,		/**< List of face indices, one list per leaf */
			DirEntry_Leafbrushes,	/**< Lists of brush indices, one list per leaf */
			DirEntry_Models,		/**< Descriptions of rigid world geometry in map */
			DirEntry_Brushes,		/**< Convex polyhedra used to describe solid space */
			DirEntry_Brushsides,	/**< Brush surfaces */
			DirEntry_Vertices,		/**< Vertices used to describe faces */
			DirEntry_Meshverts,		/**< Lists of offsets, one list per mesh */
			DirEntry_Effects,		/**< List of special map effects */
			DirEntry_Faces,			/**< Surface geometry */
			DirEntry_Lightmaps,		/**< Packed lightmap data */
			DirEntry_Lightvols,		/**< Local illumination data */
			DirEntry_Visdata,		/**< Cluster-cluster visibility data */
		};

		enum {
			FaceType_Polygon = 1,
			FaceType_Patch,
			FaceType_Mesh,
			FaceType_Billboard,
		};

		struct Texture {
			char name[64];
			int32_t flags;
			int32_t contents;
		} __attribute__ ((packed));
	} // Q3Bsp
	
	bool BspSceneFile::load(const std::string& path) {
		std::ifstream bspFile(path.c_str());
		if (!bspFile) {
			return false;
		}
		
		struct {
			char magic[4];
			int32_t version;
			Q3Bsp::DirEntry direntry[17];
		} __attribute__ ((packed)) bspHeader;
		
		if (!bspFile.read(reinterpret_cast<char*>(&bspHeader), sizeof(bspHeader))) {
			return false;
		}
		if (strncmp(BSP_HEADER_MAGIC.c_str(), bspHeader.magic, 4) != 0) {
			return false;
		}
		switch (bspHeader.version) {
			case Q3Bsp::BSP_QUAKE3_VERSION:
				break;
				
			default:
				return false;
		}
		
		if (!loadTextures(bspFile, bspHeader.direntry[Q3Bsp::DirEntry_Textures])) {
			return false;
		}
		
		if (!loadPlanes(bspFile, bspHeader.direntry[Q3Bsp::DirEntry_Planes])) {
			return false;
		}
		
		if (!loadNodes(bspFile, bspHeader.direntry[Q3Bsp::DirEntry_Nodes])) {
			return false;
		}
		
		if (!loadLeaves(bspFile, bspHeader.direntry[Q3Bsp::DirEntry_Leaves])) {
			return false;
		}
		
		if (!loadLeafFaces(bspFile, bspHeader.direntry[Q3Bsp::DirEntry_Leaves])) {
			return false;
		}
		
		if (!loadModels(bspFile, bspHeader.direntry[Q3Bsp::DirEntry_Models])) {
			return false;
		}
		
		if (!loadVertices(bspFile, bspHeader.direntry[Q3Bsp::DirEntry_Vertices])) {
			return false;
		}
		
		if (!loadFaces(bspFile, bspHeader.direntry[Q3Bsp::DirEntry_Faces])) {
			return false;
		}
		
		return true;
	}
	
	bool BspSceneFile::loadBspDirEntry(std::istream& bspStream, const Q3Bsp::DirEntry& entry, SharedArray<uint8_t>::Type& outData) {
		if (!bspStream.seekg(entry.offset, std::ios::beg)) {
			return false;
		}
		
		outData.reset(new uint8_t[entry.length]);
		if (!bspStream.read(reinterpret_cast<char*>(outData.get()), entry.length)) {
			return false;
		}
		return true;
	}		
	
	bool BspSceneFile::loadTextures(std::istream& bspStream, const Q3Bsp::DirEntry& texturesEntry) {
		SharedArray<uint8_t>::Type texturesData;
		if (!loadBspDirEntry(bspStream, texturesEntry, texturesData)) {
			return false;
		}
		
		return true;
	}
	
	bool BspSceneFile::loadPlanes(std::istream& bspStream, const Q3Bsp::DirEntry& planesEntry) {
		if (!bspStream.seekg(planesEntry.offset, std::ios::beg)) {
			return false;
		}
		
		std::size_t numPlanes(planesEntry.length / sizeof(Q3Bsp::Plane));
		m_planes.reserve(numPlanes);
		
		if (!bspStream.read(reinterpret_cast<char*>(&m_planes[0]), planesEntry.length)) {
			return false;
		}
		return true;
	}
	
	bool BspSceneFile::loadNodes(std::istream& bspStream, const Q3Bsp::DirEntry& nodesEntry) {
		if (!bspStream.seekg(nodesEntry.offset, std::ios::beg)) {
			return false;
		}
		
		std::size_t numNodes(nodesEntry.length / sizeof(Q3Bsp::Node));
		m_nodes.reserve(numNodes);
		
		if (!bspStream.read(reinterpret_cast<char*>(&m_nodes[0]), nodesEntry.length)) {
			return false;
		}
		return true;
	}
	
	bool BspSceneFile::loadLeaves(std::istream& bspStream, const Q3Bsp::DirEntry& leavesEntry) {
		if (!bspStream.seekg(leavesEntry.offset, std::ios::beg)) {
			return false;
		}
		
		std::size_t numLeaves(leavesEntry.length / sizeof(Q3Bsp::Leaf));
		m_leaves.reserve(numLeaves);
		
		if (!bspStream.read(reinterpret_cast<char*>(&m_leaves[0]), leavesEntry.length)) {
			return false;
		}
		return true;
	}
	
	bool BspSceneFile::loadLeafFaces(std::istream& bspStream, const Q3Bsp::DirEntry& leafFacesEntry) {
		if (!bspStream.seekg(leafFacesEntry.offset, std::ios::beg)) {
			return false;
		}
		
		std::size_t numLeafFaces(leafFacesEntry.length / sizeof(Q3Bsp::LeafFace));
		m_leafFaces.reserve(numLeafFaces);

		if (!bspStream.read(reinterpret_cast<char*>(&m_leafFaces[0]), leafFacesEntry.length)) {
			return false;
		}
		return true;
	}

	bool BspSceneFile::loadModels(std::istream& bspStream, const Q3Bsp::DirEntry& modelsEntry) {
		struct BspModel {
			float minCoord[3];
			float maxCoord[3];
			int32_t face;
			int32_t numFaces;
			int32_t brush;
			int32_t numBrushes;
		} __attribute__ ((packed));
		
		SharedArray<uint8_t>::Type modelsData;
		if (!loadBspDirEntry(bspStream, modelsEntry, modelsData)) {
			return false;
		}
		
		return true;
	}
	
	bool BspSceneFile::loadVertices(std::istream& bspStream, const Q3Bsp::DirEntry& verticesEntry) {
		if (!bspStream.seekg(verticesEntry.offset, std::ios::beg)) {
			return false;
		}
		
		std::size_t numVertices(verticesEntry.length / sizeof(Q3Bsp::Vertex));
		m_vertices.reserve(numVertices);
		
		if (!bspStream.read(reinterpret_cast<char*>(&m_vertices[0]), verticesEntry.length)) {
			return false;
		}
		return true;
	}
	
	bool BspSceneFile::loadFaces(std::istream& bspStream, const Q3Bsp::DirEntry& facesEntry) {
		if (!bspStream.seekg(facesEntry.offset, std::ios::beg)) {
			return false;
		}
		
		std::size_t numFaces(facesEntry.length / sizeof(Q3Bsp::Face));
		m_faces.reserve(numFaces);

		if (!bspStream.read(reinterpret_cast<char*>(&m_faces[0]), facesEntry.length)) {
			return false;
		}
		return true;
	}
	
} // TDZ
