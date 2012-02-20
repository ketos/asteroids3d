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

#include "C3DSMeshNormalCalculator.h"

/******************************************************************************/

#include <algorithm>
#include <map>
#include <set>
#include <iterator>

/******************************************************************************/

void C3DSMeshNormalCalculator::calculate() {
	
	// list of references into the source mesh for each particular group
	typedef std::map< Uint32, std::vector<Uint16> > GroupRefList;
	
	for ( unsigned int i = 0; i < m_meshReader.meshes().size(); ++i ) {
		const C3DSMeshReader::Mesh &mesh = m_meshReader.meshes()[i];
		
		// if there is no smoothing group list in the source mesh it is the same
		// as if any face where assigned to group 0
		std::vector<Uint32> smoothingGroup = mesh.smoothingGroup;
		if ( smoothingGroup.size() == 0 ) {
			smoothingGroup.resize(mesh.faces.size(), 0);
		}
		
		// list of faces for each group
		GroupRefList groupFaces;
		GroupRefList groupVertices;
		
		// for each vertex a list with the normal for a particular smoothing group
		std::vector< std::map<Uint32, math3d::vec3> > vertexNormals(mesh.vertices.size());
		
		for ( unsigned int i = 0; i < mesh.faces.size(); ++i ) {
			
			// add this face to the appropriate group list
			groupFaces[smoothingGroup[i]].push_back(i);
			
			// smoothing group 0 is a special case and will be handled later
			if ( smoothingGroup[i] != 0 ) {
				const Uint16 *indices = mesh.faces[i].indices;
				
				// create a list of all the vertices in this group
				groupVertices[smoothingGroup[i]].push_back(indices[0]);
				groupVertices[smoothingGroup[i]].push_back(indices[1]);
				groupVertices[smoothingGroup[i]].push_back(indices[2]);
				
				
				math3d::vec3 faceNormal = calculateFaceNormal(mesh, i);
				
				// for all smoothing groups this face belongs to, add the normal
				for ( Uint32 j = 0; j < 32; ++j ) {
					Uint32 groupID = 1 << j;
					
					if ( smoothingGroup[i] & groupID ) {
						vertexNormals[indices[0]][j] += faceNormal;
						vertexNormals[indices[1]][j] += faceNormal;
						vertexNormals[indices[2]][j] += faceNormal;
					}
				}
				
			} // end if smoothing group != 0
			
		}	// end for all faces
		
		// sort list and remove all duplicate vertex indices
		for ( GroupRefList::iterator i = groupVertices.begin(); i != groupVertices.end(); ++i ) {
			std::vector<Uint16> &vertexRefList = (*i).second;
			
			sort(vertexRefList.begin(), vertexRefList.end());
			vertexRefList.erase(
				unique(vertexRefList.begin(), vertexRefList.end()),
				vertexRefList.end()
			);
		}
		
		
		// create the new mesh and calculate the new vertices and faces
		// (some vertices must be duplicated)
		
		m_meshes.push_back(Mesh());
		Mesh &newMesh = m_meshes.back();
		
		newMesh.name = mesh.name;
		newMesh.faceMaterials = mesh.faceMaterials;
		newMesh.localCoordSys = mesh.localCoordSys;
		newMesh.vertices.resize(mesh.vertices.size());
		newMesh.normals.resize(mesh.vertices.size());
		newMesh.mapCoords.resize(mesh.mapCoords.size());
		
		// marks if a vertex from the original mesh has already been used
		std::vector<bool> vertexUsed(mesh.vertices.size(), false);
		
		// if a vertex must be duplicated the new position where it must be stored
		// is saved in newIndex
		std::vector<Uint32> newIndex(mesh.vertices.size());
		
		// for all group values ( except for value 0 ) 
		for ( GroupRefList::iterator i = groupVertices.begin(); i != groupVertices.end(); ++i ) {
			Uint32 groupID = i->first;
			std::vector<Uint16> &vertexRefList = i->second;
			
			// calculate how many new vertices must be created
			Uint32 newVertexCount = 0;
			
			for ( unsigned int i = 0, _n = groupVertices[groupID].size(); i < _n; ++i ) {
				Uint32 idx = vertexRefList[i];
				
				if ( vertexUsed[idx] ) {
					newIndex[idx] = newMesh.vertices.size() + newVertexCount;
					newVertexCount++;
				}
				else {
					newIndex[idx] = idx;
				}
			}
			
			// resize the vertex array to create room for the new vertices
			resizeArrays(newMesh, newMesh.vertices.size() + newVertexCount);
			
			// write the vertex data
			for ( unsigned int i = 0, _n = groupVertices[groupID].size(); i < _n; ++i ) {
				std::vector<Uint16> &vertexRefList = groupVertices[groupID];
				
				Uint32 oldIdx = vertexRefList[i];
				Uint32 newIdx = newIndex[oldIdx];
				
				// the final normal is calculated; groupID could be 3 ( bitpattern 0...011 ) which means
				// the normals from group 1 and 2 have to be used (hope this is correct)
				math3d::vec3 normal;
				
				for ( Uint32 j = 0; j < 32; ++j ) {
					Uint32 gID = 1 << j;
					
					if ( groupID & gID ) {
						normal += vertexNormals[oldIdx][j];
					}
				}
				
				normalize(normal);
				
				writeVertexData(newMesh, mesh, newIdx, oldIdx, normal);
				vertexUsed[oldIdx] = true;
			}
			
			// add faces to the list
			std::vector<Uint16> &faceRefList = groupFaces[groupID];
			for ( unsigned int i = 0, _n = faceRefList.size(); i < _n; ++i ) {
				Face face;
				
				Uint32 idx = faceRefList[i];
				
				face.faceFlag = mesh.faces[idx].faceFlag;
				face.indices[0] = newIndex[mesh.faces[idx].indices[0]];
				face.indices[1] = newIndex[mesh.faces[idx].indices[1]];
				face.indices[2] = newIndex[mesh.faces[idx].indices[2]];
				
				newMesh.faces.push_back(face);
			}
			
		}	// end for all groups
		
		{
			GroupRefList::iterator i = groupFaces.begin();
			
			// if there are any faces for group 0 the groupID of the first element
			// in groupFaces will be 0
			if ( i->first == 0 ) {
				std::vector<Uint16> &faceRefList = i->second;
				
				for ( unsigned int i = 0, _n = faceRefList.size(); i < _n; ++i ) {
					math3d::vec3 faceNormal = calculateFaceNormal(mesh, faceRefList[i]);
					
					Uint32 idx = faceRefList[i];
					
					for ( int j = 0; j < 3; ++j ) {
						Uint32 vIndex = mesh.faces[idx].indices[j];
						
						if ( vertexUsed[vIndex] ) {
							newIndex[vIndex] = newMesh.vertices.size();
							resizeArrays(newMesh, newMesh.vertices.size() + 1);
						}
						else {
							newIndex[vIndex] = vIndex;
						}
						
						writeVertexData(newMesh, mesh, newIndex[vIndex], vIndex, faceNormal);
						vertexUsed[vIndex] = true;
					}
					
					// add the face to the facelist and correct vertex references
					{
						Face face;
						
						face.faceFlag = mesh.faces[idx].faceFlag;
						face.indices[0] = newIndex[mesh.faces[idx].indices[0]];
						face.indices[1] = newIndex[mesh.faces[idx].indices[1]];
						face.indices[2] = newIndex[mesh.faces[idx].indices[2]];
						
						newMesh.faces.push_back(face);
					}
					
				}	// end for all faces
			}	// end if smoothing group = 0
		}
		
	}	// end for all meshes
}


/******************************************************************************/

void C3DSMeshNormalCalculator::resizeArrays(Mesh &mesh, Uint32 newSize) {
	mesh.vertices.resize(newSize);
	mesh.normals.resize(newSize);
						
	// only create mapping coordinates if there are any in the source mesh
	if ( mesh.mapCoords.size() != 0 ) {
		mesh.mapCoords.resize(newSize);
	}
}

void C3DSMeshNormalCalculator::writeVertexData(
	Mesh& newMesh,
	const C3DSMeshReader::Mesh& mesh,
	Uint32 newIdx,
	Uint32 oldIdx,
	math3d::vec3 normal)
{
	
	newMesh.vertices[newIdx] = mesh.vertices[oldIdx];
	newMesh.normals[newIdx] = normal;
				
	// assign mapping coordinates only if there are any in the source mesh
	if ( mesh.mapCoords.size() != 0 ) {
		newMesh.mapCoords[newIdx] = mesh.mapCoords[oldIdx];
	}
	
	//cout << newMesh.vertices[newIdx] << endl;
	//cout << newIdx << "\t"<< oldIdx << endl;
}

math3d::vec3 C3DSMeshNormalCalculator::calculateFaceNormal(const C3DSMeshReader::Mesh& mesh, Uint16 faceIndex) {
	const Uint16 *indices = mesh.faces[faceIndex].indices;
		
	return
		normalized(
			cross(
				mesh.vertices[indices[1]] - mesh.vertices[indices[0]],
				mesh.vertices[indices[2]] - mesh.vertices[indices[0]]
			)
		);
}
