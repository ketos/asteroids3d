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

#ifndef C3DSMATERIALREADER_H
#define C3DSMATERIALREADER_H

/******************************************************************************/

#include "C3DSReaderBase.h"

#include <vector>

/******************************************************************************/

class C3DSMaterialReader : public virtual C3DSReaderBase {
public:
	C3DSMaterialReader(SDL_RWops* rw):C3DSReaderBase(rw){};

public:
	struct TextureMap {
		Uint16 id;	// id for type identification ( opacity map, specular map, ...)
		std::string filename;
		float uScale;
		float vScale;
		float uOffset;
		float vOffset;
		float rotation;
	};

	struct Material {
		std::string name;
		float colorAmbient[3];
		float colorDiffuse[3];
		float colorSpecular[3];
		
		float shininess;
		float shininessStrength;
		
		float transparency;
		
		bool twoSided;
		bool wireFrame;
		
		std::vector<TextureMap> texMaps;
	};
	
	const std::vector<Material>& materials() const {
		return m_materials;
	}
	
	std::vector<Material>& materials() {
		return m_materials;
	}
	
protected:	
	virtual bool onChunk(const Chunk& chunk);
	
	std::vector<Material> m_materials;
};

/******************************************************************************/

#endif
