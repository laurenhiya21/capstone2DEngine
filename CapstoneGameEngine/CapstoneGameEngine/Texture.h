#pragma once
#include <glew.h>

// Stores a texture for an Object and any texture related functions
class Texture
{
	private:
		unsigned ID; // id opengl uses to reference this paticular texture
		unsigned width; // size of texture (pixels)
		unsigned height;
		unsigned internalFmt; // format of the texture
		unsigned wrapS; // wrapping mode on s axis
		unsigned wrapT; // wrapping mode on t axis
		unsigned filterMin; //filter mode if texter pixels < screen pixels
		unsigned filterMax; //filter mode if texture pixels > screen pixels

	public:

		// constructor
		Texture(unsigned w = 0, unsigned h = 0, unsigned iFmt = GL_RGB, unsigned ws = GL_REPEAT, unsigned wt = GL_REPEAT, unsigned filtMin = GL_LINEAR, unsigned filtMax = GL_LINEAR);

};
