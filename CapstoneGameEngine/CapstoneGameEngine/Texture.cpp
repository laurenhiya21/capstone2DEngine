#include "Texture.h"

// constructor with default paramaters
Texture::Texture(unsigned w, unsigned h, unsigned iFmt, unsigned ws, unsigned wt, unsigned filtMin, unsigned filtMax)
{
	width = w;
	height = h;
	internalFmt = iFmt;
	wrapS = ws;
	wrapT = wt;
	filterMin = filtMin;
	filterMax = filtMax;

	// generates the texture on the openGl side and sets the id
	glGenTextures(1, &ID);
}
