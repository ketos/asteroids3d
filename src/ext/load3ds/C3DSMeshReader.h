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

#ifndef C3DSMESHREADER_H
#define C3DSMESHREADER_H

/******************************************************************************/

#include "C3DSReaderBase.h"
#include "math3d++.h"

#include <string>
#include <vector>

/******************************************************************************/

class C3DSMeshReader : public virtual C3DSReaderBase {
public:
	C3DSMeshReader(SDL_RWops* rw):C3DSReaderBase(rw){};

public:
	struct FaceMaterial {
		std::string name;
		std::vector<Uint16> faces;
	};
	
	struct MapCoord {
		float u;
		float v;
	};
	
	struct Face {
		Uint16 indices[3]; // corner A, B, C
		Uint16 faceFlag; // bit 0: CA visible; bit 1: BC visible; bit 2: AB visible
	};
	
	struct Mesh {
		std::string name;
		std::vector<math3d::vec3> vertices;
		std::vector<Face> faces;
		std::vector<FaceMaterial> faceMaterials;
		std::vector<Uint32> smoothingGroup;
		std::vector<MapCoord> mapCoords;
		math3d::mat4 localCoordSys;
	};
	
	
	const std::vector<Mesh>& meshes() const {
		return m_meshes;
	}
	
	std::vector<Mesh>& meshes() {
		return m_meshes;
	}
	
protected:
	virtual bool onChunk(const Chunk& chunk);

	std::vector<Mesh> m_meshes;
	
private:
	std::string m_currentObjectName;
};

/******************************************************************************/

#endif

