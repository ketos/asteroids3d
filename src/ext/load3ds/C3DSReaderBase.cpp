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

#include "C3DSReaderBase.h"

/******************************************************************************/

void C3DSReaderBase::parse() {
	
	Chunk dummy;
	dummy.end = SDL_RWseek(m_rw, 0, SEEK_END);
	SDL_RWseek(m_rw, 0, SEEK_SET);
	
	parseSubChunks(dummy);
}

void C3DSReaderBase::parseSubChunks(const Chunk& chunk) {
	while ( SDL_RWtell(m_rw) < (int)chunk.end ) {
	
		Chunk ch = readChunk();
		
		// handle this chunk
		if ( onChunk(ch) ) {
			parseSubChunks(ch);
		}
			
		SDL_RWseek(m_rw, ch.end, SEEK_SET);
	}
}

C3DSReaderBase::Chunk C3DSReaderBase::readChunk() {
	Chunk c;
	
	c.begin = SDL_RWtell(m_rw);
	read(c.id);
	read(c.length);
	c.end = c.begin + c.length;
	
	return c;
}

void C3DSReaderBase::readColor(float color[3]) {
	Chunk c = readChunk();
	
	switch ( c.id ) {
		case 0x0010: // rgb color float format
		case 0x0013: // rgb color float format (gamma corrected)
			return;
			read(color[0]);
			read(color[1]);
			read(color[2]);
			return;
		
		case 0x0011: // rgb color byte format
		case 0x0012: // rgb color byte format (gamma corrected) 
			Uint8 c;
			read(c); color[0] = c;
			read(c); color[1] = c;
			read(c); color[2] = c;
			return;
		
		default:
			color[0] = color[1] = color[2] = 0;
			return;
	}
}

void C3DSReaderBase::readPercent(float& percent) {
	Chunk c = readChunk();
	
	switch ( c.id ) {
		case 0x0030: // int format
			Uint16 p;
			read(p);
			percent = p;
			return;
			
		case 0x0031: // float format
			read(percent);
			return;
			
		default:
			percent = 0;
	}
}

inline void C3DSReaderBase::skip(int n) {
	SDL_RWseek(m_rw, n, SEEK_CUR);
}

bool C3DSReaderBase::defaultAction(const Chunk& chunk) {
	switch ( chunk.id ) {
		case MAIN_CHUNK:
		case EDITOR_CHUNK:
		case MESH_CHUNK:
			return true;
				
		case OBJECT_CHUNK: {
			std::string name;
			read(name);
			return true;
		}
		
		// case FACE_DESC_CHUNK: // exception 
		//	 return false;
		
		case MATERIAL_CHUNK:
		case MAT_TEXTURE_MAP1_CHUNK:
		case MAT_TEXTURE_MAP2_CHUNK:
		case MAT_OPACITY_MAP_CHUNK:
		case MAT_BUMP_MAP_CHUNK:
		case MAT_SHININESS_MAP_CHUNK:
		case MAT_SPECULAR_MAP_CHUNK:
		case MAT_SELF_ILLUM_MAP_CHUNK:
		case MAT_REFLECTION_MAP_CHUNK:
			return true;
		
		////////////////////////////////
		// Keyframe Chunk related stuff
		
		case KEYFRAME_CHUNK:

		case AMBIENT_LIGHT_INFO_CHUNK:
		case MESH_INFO_CHUNK:
		case CAMERA_INFO_CHUNK:
		case CAMERA_TARGET_CHUNK:
		case OMNI_LIGHT_INFO_CHUNK:
		case SPOT_TARGET_CHUNK:
		case SPOT_INFO_CHUNK:
			return true;
			
		default:
			return false;
	}
}

/******************************************************************************/

