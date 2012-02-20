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

/******************************************************************************/

#include "C3DSMeshReader.h"

/******************************************************************************/

bool C3DSMeshReader::onChunk(const Chunk& chunk) {
		switch ( chunk.id ) {
		case OBJECT_CHUNK: {
			read(m_currentObjectName);
			
			return true;
		}
		
		case MESH_CHUNK: {
			// create a new Mesh
			m_meshes.push_back(Mesh());
			
			return true;
		}
		
		case VERTEX_LIST: {
			Mesh &m = m_meshes.back();
			m.name = m_currentObjectName;
			
			Uint16 nvertices;
			read(nvertices);
			
			for ( int i = 0; i < nvertices; ++i ) {
				math3d::vec3 v;
				read(v);
				m.vertices.push_back(v);
			}
			
			return false;
		}	
		case FACE_DESC_CHUNK: {
			Mesh &m = m_meshes.back();
			
			Uint16 nfaces;
			read(nfaces);
			
			for ( int i = 0; i < nfaces; ++i ) {
				Face f;
				read(f.indices[0]);
				read(f.indices[1]);
				read(f.indices[2]);
				read(f.faceFlag);
				
				m.faces.push_back(f);
			}
			
			return true;
		}
		
		case FACE_MATERIAL: {
			Mesh &m = m_meshes.back();
			m.faceMaterials.push_back(FaceMaterial());
			
			FaceMaterial &mat = m.faceMaterials.back();
			Uint16 nentries;
			
			read(mat.name);
			read(nentries);
			
			for ( int i = 0; i < nentries; ++i ) {
				Uint16 face;
				read(face);
				mat.faces.push_back(face);
			}
			
			return false;
		}
		
		case SMOOTH_GROUP: {
			Mesh &m = m_meshes.back();
			
			// one Uint32 for each face
			Uint16 nentries = (chunk.length - 6) / 4;
			
			for ( int i = 0; i < nentries; ++i ) {
				Uint32 value;
				read(value);
				m.smoothingGroup.push_back(value);
			}
			
			return false;
		}
		
		case MAP_COORDS: {
			Mesh &m = m_meshes.back();
			
			Uint16 nvertices;
			read(nvertices);
			
			for ( int i = 0; i < nvertices; ++i ) {
				MapCoord coord;
				read(coord);
				m.mapCoords.push_back(coord);
			}
			
			return false;
		}
		
		case LOCAL_COORD_SYS: {
			Mesh &m = m_meshes.back();
			
			math3d::vec3 x1, x2, x3, o;
			
			read(x1);
			read(x2);
			read(x3);
			read(o);
			
			math3d::mat4 mat(
				x1[0], x2[0], x3[0], o[0],
				x1[1], x2[1], x3[1], o[1],
				x1[2], x2[2], x3[2], o[2],
				0, 0, 0, 1
			);
			
			m.localCoordSys = mat;
			
			return false;
		}
		
		default:
			return defaultAction(chunk);
		}
	}
	
/******************************************************************************/
