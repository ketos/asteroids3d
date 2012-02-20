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

#ifndef C3DSREADERBASE_H
#define C3DSREADERBASE_H

/******************************************************************************/

#include "C3DSFormat.h"

#include "SDL_rwops.h"
#include <string>

/******************************************************************************/

class C3DSReaderBase : public C3DSFormat {
public:
	explicit C3DSReaderBase(SDL_RWops* rw):m_rw(rw){}
	virtual ~C3DSReaderBase(){};
	void parse();
	
protected:
	SDL_RWops *m_rw;
	
	virtual bool onChunk(const Chunk& chunk) = 0;
	
	Chunk readChunk();

	template <class T>
	void read(T& var);
	
	void readColor(float color[3]);
	void readPercent(float& percent);
	
	// skip n byte in the input stream
	void skip(int n);
	
	bool defaultAction(const Chunk& c);
	
private:
	void parseSubChunks(const Chunk& chunk);
};

/******************************************************************************/

template <class T>
inline void C3DSReaderBase::read(T& var) {
	SDL_RWread(m_rw, &var, sizeof(var), 1);
}

template <>
inline void C3DSReaderBase::read(std::string& str) {
	char c;
	read(c);
	
	str.clear();
	while ( c != '\0' ) {
		str += c;
		read(c);
	}
}

/******************************************************************************/

#endif
