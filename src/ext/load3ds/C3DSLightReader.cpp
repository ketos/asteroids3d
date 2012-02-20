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

#include "C3DSLightReader.h"

bool C3DSLightReader::onChunk(const Chunk& chunk) {
	
	switch ( chunk.id ) {
		case LIGHT_CHUNK: {
			Light light;
			read(light.position);
			m_lights.push_back(light);
			return true;
		}
			
		case SPOT_LIGHT_CHUNK: {
			Light& light = m_lights.back();
			
			light.isSpotLight = true;
			read(light.spotTarget);
			read(light.hotSpot);
			read(light.falloff);
			
			return false;
		}
		
		case LIGHT_OFF: {
			m_lights.back().lightOff = true;
			return false;
		}
		
		case LIGHT_ATTENUATION_ON: {
			m_lights.back().attenuationOn = true;
			return false;
		}
			
		default:
			return defaultAction(chunk);
	}
}

/******************************************************************************/
