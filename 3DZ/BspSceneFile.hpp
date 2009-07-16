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
#include <map>

#include <3DZ/Mesh.hpp>
#include <3DZ/Plane.hpp>
#include <3DZ/Scene.hpp>

namespace TDZ {
		
	namespace Q3Bsp {
		struct DirEntry;
		struct Plane;
		struct Vertex;
		struct Node;
		struct Leaf;
		struct Face;
		struct LeafFace;
	} // Q3Bsp
	
	class BspSceneFile : public Scene {
	public:
		bool load(const std::string& path);
		
	private:		
		bool loadBspDirEntry(std::istream& bspStream, const Q3Bsp::DirEntry& entry, SharedArray<uint8_t>::Type& outData);
		bool loadTextures(std::istream& bspStream, const Q3Bsp::DirEntry& texturesEntry);
		bool loadPlanes(std::istream& bspStream, const Q3Bsp::DirEntry& planesEntry);
		bool loadNodes(std::istream& bspStream, const Q3Bsp::DirEntry& nodesEntry);
		bool loadLeaves(std::istream& bspStream, const Q3Bsp::DirEntry& leavesEntry);
		bool loadLeafFaces(std::istream& bspStream, const Q3Bsp::DirEntry& leafFacesEntry);
		bool loadModels(std::istream& bspStream, const Q3Bsp::DirEntry& modelsEntry);
		bool loadVertices(std::istream& bspStream, const Q3Bsp::DirEntry& verticesEntry);
		bool loadFaces(std::istream& bspStream, const Q3Bsp::DirEntry& facesEntry);

		typedef std::vector<Q3Bsp::LeafFace> LeafFaceVec;
		typedef std::vector<Q3Bsp::Plane> PlaneVec;
		typedef std::vector<Q3Bsp::Vertex> VertexVec;
		typedef std::vector<Q3Bsp::Face> FaceVec;
		typedef std::vector<Q3Bsp::Node> NodeVec;
		typedef std::vector<Q3Bsp::Leaf> LeafVec;
		
		PlaneVec m_planes;
		VertexVec m_vertices;
		FaceVec m_faces;
		NodeVec m_nodes;
		LeafVec m_leaves;
		LeafFaceVec m_leafFaces;
	};

	namespace Q3Bsp {
		struct DirEntry {
			int32_t offset;
			int32_t length;
		} __attribute__ ((packed));
		
		struct Plane {
			float normal[3];
			float distance;
		} __attribute__ ((packed));
		
		struct Vertex {
			float position[3];
			float textureCoord[2][2];
			float normal[3];
			uint8_t color[4];
		} __attribute__ ((packed));
		
		struct Face {
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
		
		struct Node {
			int32_t plane;
			int32_t children[2];
			int32_t minCoord[3];
			int32_t maxCoord[3];
		} __attribute__ ((packed));
		
		struct Leaf {
			int32_t cluster;
			int32_t area;
			int32_t minCoord[3];
			int32_t maxCoord[3];
			int32_t face;
			int32_t numFaces;
			int32_t brush;
			int32_t numBrushes;
		} __attribute__ ((packed));
		
		struct LeafFace {
			int32_t face;
		} __attribute__ ((packed));		
	} // Q3Bsp
	
} // TDZ

#endif /* TDZ_BSPSCENEFILE_HPP */
