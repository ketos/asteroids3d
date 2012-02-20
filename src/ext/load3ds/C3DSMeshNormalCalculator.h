/*
	3DSLoader - A 3D Studio File Loader
	Copyright (c) 2004, Trenkwalder Markus
	All rights reserved. 
	
	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:
	
	- Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	  
	- Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.
	  
	- Neither the name of the 3DSLoader's copyright owner nor the names
	  of its contributors may be used to endorse or promote products
	  derived from this software without specific prior written permission.
	  
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
	TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
	PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
	LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
	
	Contact info:
	email: trenki2@gmx.net web: trenki.50free.org
*/

#ifndef C3DSMESHNORMALCALCULATOR_H
#define C3DSMESHNORMALCALCULATOR_H

/******************************************************************************/

#include "C3DSMeshReader.h"

/******************************************************************************/

class C3DSMeshNormalCalculator {
public:
	C3DSMeshNormalCalculator(const C3DSMeshReader& mr):m_meshReader(mr){}

	// the face struct from C3DSMeshReader cannot be used because the indices are
	// only Uint16 and we need Uint32 because the number of vertices can grow
	struct Face {
		Uint32 indices[3]; // corner A, B, C
		Uint16 faceFlag; // bit 0: CA visible; bit 1: BC visible; bit 2: AB visible
	};

	struct Mesh {
		std::string name;
		std::vector<math3d::vec3> vertices;
		std::vector<math3d::vec3> normals;
		std::vector<Face> faces;
		std::vector<C3DSMeshReader::FaceMaterial> faceMaterials;
		std::vector<C3DSMeshReader::MapCoord> mapCoords;
		math3d::mat4 localCoordSys;
	};
	
	void calculate();

	const std::vector<Mesh>& meshes() const {
		return m_meshes;
	}
	
	std::vector<Mesh>& meshes() {
		return m_meshes;
	}

protected:
	std::vector<Mesh> m_meshes;

private:
	const C3DSMeshReader& m_meshReader;
	
	
	math3d::vec3 calculateFaceNormal(const C3DSMeshReader::Mesh& mesh, Uint16 faceIndex);
	
	void resizeArrays(Mesh& mesh, Uint32 newSize);
	
	void writeVertexData(
		Mesh& newMesh,
		const C3DSMeshReader::Mesh& mesh,
		Uint32 newIdx,
		Uint32 oldIdx,
		math3d::vec3 normal
	);
	
};

/******************************************************************************/

#endif
