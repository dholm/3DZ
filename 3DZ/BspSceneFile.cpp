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
	}
	
	bool BspSceneFile::load(const std::string& path) {
		std::ifstream bspFile(path.c_str());
		if (!bspFile) {
			return false;
		}
		
		struct {
			char magic[4];
			int32_t version;
			BspDirEntry direntry[17];
		} __attribute__ ((packed)) bspHeader;
		
		if (!bspFile.read(reinterpret_cast<char*>(&bspHeader), sizeof(bspHeader))) {
			return false;
		}
		if (strncmp(BSP_HEADER_MAGIC.c_str(), bspHeader.magic, 4) != 0) {
			return false;
		}
		switch (bspHeader.version) {
			case BSP_QUAKE3_VERSION:
				break;
				
			default:
				return false;
		}
		
		if (!loadPlanes(bspFile, bspHeader.direntry[DirEntry_Planes])) {
			return false;
		}
		
		if (!loadNodes(bspFile, bspHeader.direntry[DirEntry_Planes])) {
			return false;
		}
		
		if (!loadLeaves(bspFile, bspHeader.direntry[DirEntry_Leaves])) {
			return false;
		}
		
		if (!loadLeafFaces(bspFile, bspHeader.direntry[DirEntry_Leaves])) {
			return false;
		}
		
		if (!loadModels(bspFile, bspHeader.direntry[DirEntry_Models])) {
			return false;
		}
		
		if (!loadVertices(bspFile, bspHeader.direntry[DirEntry_Vertices])) {
			return false;
		}
		
		if (!loadFaces(bspFile, bspHeader.direntry[DirEntry_Faces])) {
			return false;
		}
		
		return true;
	}
	
	bool BspSceneFile::loadBspDirEntry(std::istream& bspStream, const BspDirEntry& entry, SharedArray<uint8_t>::Type& outData) {
		if (!bspStream.seekg(entry.offset, std::ios::beg)) {
			return false;
		}
		
		outData.reset(new uint8_t[entry.length]);
		if (!bspStream.read(reinterpret_cast<char*>(outData.get()), entry.length)) {
			return false;
		}
		return true;
	}		
	
	bool BspSceneFile::loadPlanes(std::istream& bspStream, const BspDirEntry& planesEntry) {
		struct BspPlane {
			float normal[3];
			float distance;
		} __attribute__ ((packed));
		
		SharedArray<uint8_t>::Type planesData;
		if (!loadBspDirEntry(bspStream, planesEntry, planesData)) {
			return false;
		}
		
		return true;
	}
	
	bool BspSceneFile::loadNodes(std::istream& bspStream, const BspDirEntry& nodesEntry) {
		struct BspNode {
			int32_t plane;
			int32_t children[2];
			int32_t minCoord[3];
			int32_t maxCoord[3];
		} __attribute__ ((packed));
		
		SharedArray<uint8_t>::Type nodesData;
		if (!loadBspDirEntry(bspStream, nodesEntry, nodesData)) {
			return false;
		}
		
		return true;
	}
	
	bool BspSceneFile::loadLeaves(std::istream& bspStream, const BspDirEntry& LeavesEntry) {
		struct BspLeaf {
			int32_t cluster;
			int32_t area;
			int32_t minCoord[3];
			int32_t maxCoord[3];
			int32_t face;
			int32_t numFaces;
			int32_t brush;
			int32_t numBrushes;
		} __attribute__ ((packed));
		
		SharedArray<uint8_t>::Type LeavesData;
		if (!loadBspDirEntry(bspStream, LeavesEntry, LeavesData)) {
			return false;
		}

		return true;
	}
	
	bool BspSceneFile::loadLeafFaces(std::istream& bspStream, const BspDirEntry& leafFacesEntry) {
		struct BspLeafFace {
			int32_t face;
		} __attribute__ ((packed));

		SharedArray<uint8_t>::Type leafFacesData;
		if (!loadBspDirEntry(bspStream, leafFacesEntry, leafFacesData)) {
			return false;
		}
		
		return true;
	}

	bool BspSceneFile::loadModels(std::istream& bspStream, const BspDirEntry& modelsEntry) {
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
	
	bool BspSceneFile::loadVertices(std::istream& bspStream, const BspDirEntry& verticesEntry) {
		struct BspVertex {
			float position[3];
			float textureCoord[2][2];
			float normal[3];
			uint8_t color[4];
		} __attribute__ ((packed));
		
		SharedArray<uint8_t>::Type verticesData;
		if (!loadBspDirEntry(bspStream, verticesEntry, verticesData)) {
			return false;
		}
		
		return true;
	}
	
	bool BspSceneFile::loadFaces(std::istream& bspStream, const BspDirEntry& facesEntry) {
		enum {
			BspFaceType_Polygon = 1,
			BspFaceType_Patch,
			BspFaceType_Mesh,
			BspFaceType_Billboard,
		};
		
		struct BspFace {
			int32_t texture;
			int32_t effect;
			int32_t type;
			int32_t vertex;
			int32_t numVertices;
			int32_t meshVertex;
			int32_t numMeshVertices;
			int32_t lightmap;
			int32_t lightmapStart[2];
			int32_t lightmapSize[2];
			float lightmapOrigin[3];
			float lightmapVectors[2][3];
			float normal[3];
			int32_t size[2];
		} __attribute__ ((packed));
		
		SharedArray<uint8_t>::Type facesData;
		if (!loadBspDirEntry(bspStream, facesEntry, facesData)) {
			return false;
		}
		
		return true;
	}
	
} // TDZ
