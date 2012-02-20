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

#include "C3DSMaterialReader.h"

/******************************************************************************/

bool C3DSMaterialReader::onChunk(const Chunk& chunk) {
	
	Material &mat = m_materials.back(); // dangerous if m_materials is empty ?
	
	switch ( chunk.id ) {
		case MATERIAL_CHUNK:
			// create a new material
			m_materials.push_back(Material());
			return true;
		
		case MAT_NAME:
			read(mat.name);
			return false;
		
		case MAT_AMBIENT_COLOR:
			readColor(mat.colorAmbient);
			return false;
		
		case MAT_DIFFUSE_COLOR:
			readColor(mat.colorDiffuse);
			return false;
		
		case MAT_SPECULAR_COLOR:
			readColor(mat.colorSpecular);
			return false;
		
		case MAT_SHININESS:
			readPercent(mat.shininess);
			return false;
		
		case MAT_SHININESS_STRENGTH:
			readPercent(mat.shininessStrength);
			return false;
		
		case MAT_TRANSPARENCY:
			readPercent(mat.transparency);
			return false;
		
		case MAT_TWO_SIDED:
			mat.twoSided = true;
			return false;
		
		case MAT_WIRE_FRAME_ON:
			mat.wireFrame = true;
			return false;

		//////////////////
		// Texture maps
		
		case MAT_TEXTURE_MAP1_CHUNK:
		case MAT_TEXTURE_MAP2_CHUNK:
		case MAT_OPACITY_MAP_CHUNK:
		case MAT_BUMP_MAP_CHUNK:
		case MAT_SHININESS_MAP_CHUNK:
		case MAT_SPECULAR_MAP_CHUNK:
		case MAT_SELF_ILLUM_MAP_CHUNK:
		case MAT_REFLECTION_MAP_CHUNK:
			// create a new TextureMap object
			mat.texMaps.push_back(TextureMap());
			mat.texMaps.back().id = chunk.id;
			return true;
		
		case MAP_FILENAME:
			read(mat.texMaps.back().filename);
			return false;
		
		case MAP_V_SCALE:
			read(mat.texMaps.back().vScale);
			return false;
		
		case MAP_U_SCALE:
			read(mat.texMaps.back().uScale);
			return false;
		
		case MAP_U_OFFSET:
			read(mat.texMaps.back().uOffset);
			return false;
		
		case MAP_V_OFFSET:
			read(mat.texMaps.back().vOffset);
			return false;
		
		case MAP_ROTATION:
			read(mat.texMaps.back().rotation);
			return false;
		
		default:
			return defaultAction(chunk);
	}
}

/******************************************************************************/
