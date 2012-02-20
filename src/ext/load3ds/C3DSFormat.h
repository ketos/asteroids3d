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

#ifndef C3DSFORMAT_H
#define C3DSFORMAT_H

/******************************************************************************/

#include "SDL_types.h"

/******************************************************************************/

class C3DSFormat {
protected:
	struct Chunk {
		Uint16 id;
		Uint32 length;
		Uint32 begin;
		Uint32 end;
	};
	
	enum ChunkID {
		MAIN_CHUNK 			= 0x4D4D,
		VERSION_3DS 		= 0x0002,
		
		EDITOR_CHUNK 		= 0x3D3D,
		MESH_VERSION		= 0x3D3E,
		
		OBJECT_CHUNK		= 0x4000,
		
		MESH_CHUNK			= 0x4100,
		VERTEX_LIST			= 0x4110,
		FACE_DESC_CHUNK		= 0x4120,
		FACE_MATERIAL		= 0x4130,
		SMOOTH_GROUP		= 0x4150,
		MAP_COORDS			= 0x4140,
		LOCAL_COORD_SYS		= 0x4160,
		
		LIGHT_CHUNK			= 0x4600,
		SPOT_LIGHT_CHUNK	= 0x4610,
		LIGHT_OFF			= 0x4620,
		LIGHT_ATTENUATION_ON	= 0x4625,
		
		MATERIAL_CHUNK		= 0xAFFF,
		MAT_NAME			= 0xA000,
		MAT_AMBIENT_COLOR	= 0xA010,
		MAT_DIFFUSE_COLOR	= 0xA020,
		MAT_SPECULAR_COLOR	= 0xA030,
		MAT_SHININESS		= 0xA040,
		MAT_SHININESS_STRENGTH	= 0xA041,
		MAT_TRANSPARENCY	= 0xA050,
		MAT_TRANSPARENCY_FALLOFF	= 0xA052,
		MAT_TWO_SIDED		= 0xA081,
		MAT_WIRE_FRAME_ON	= 0xA085,
		
		MAT_TEXTURE_MAP1_CHUNK	= 0xA200,
		MAT_TEXTURE_MAP2_CHUNK	= 0xA33A,
		MAT_OPACITY_MAP_CHUNK	= 0xA210,
		MAT_BUMP_MAP_CHUNK		= 0xA230,
		MAT_SHININESS_MAP_CHUNK	= 0xA33C,
		MAT_SPECULAR_MAP_CHUNK	= 0xA204,
		MAT_SELF_ILLUM_MAP_CHUNK	= 0xA33D,
		MAT_REFLECTION_MAP_CHUNK	= 0xA220,
		
		MAP_FILENAME		= 0xA300,
		MAP_V_SCALE			= 0xA354,
		MAP_U_SCALE			= 0xA356,
		MAP_U_OFFSET		= 0xA358,
		MAP_V_OFFSET		= 0xA35A,
		MAP_ROTATION		= 0xA35C,
		
		KEYFRAME_CHUNK		= 0xB000,
		AMBIENT_LIGHT_INFO_CHUNK= 0xB001,
		MESH_INFO_CHUNK		= 0xB002,
		CAMERA_INFO_CHUNK	= 0xB003,
		CAMERA_TARGET_CHUNK	= 0xB004,
		OMNI_LIGHT_INFO_CHUNK	= 0xB005,
		SPOT_TARGET_CHUNK	= 0xB006,
		SPOT_INFO_CHUNK		= 0xB007,
		FRAMES_START_END	= 0xB008,
		
		OBJECT_PIVOT_POINT	= 0xB013
	};
};



/******************************************************************************/

#endif
