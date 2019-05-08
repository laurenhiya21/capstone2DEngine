#pragma once
#include <glew.h>
#include <string>

// Stores a texture for an Object and any texture related functions
class Texture
{
	private:
		std::string name; //name of the texture

		unsigned ID; // id opengl uses to reference this paticular texture
		unsigned width; // size of texture (pixels)
		unsigned height;
		unsigned internalFmt; // format of the texture
		unsigned imageFmt; // format of the image
		unsigned wrapS; // wrapping mode on s axis
		unsigned wrapT; // wrapping mode on t axis
		unsigned filterMin; //filter mode if texter pixels < screen pixels
		unsigned filterMax; //filter mode if texture pixels > screen pixels

	public:

		// constructor
		Texture(std::string n = "NONAME", unsigned w = 0, unsigned h = 0, unsigned intFmt = GL_RGB, unsigned imgFmt = GL_RGB, unsigned ws = GL_REPEAT, unsigned wt = GL_REPEAT, unsigned filtMin = GL_LINEAR, unsigned filtMax = GL_LINEAR);

		// generates texture from image data
		void generate(unsigned w, unsigned h, unsigned char* data);

		// binds the texture as the cuurent opengl texture object
		void bind() const;

		// gettors
		std::string getName();
		unsigned getImageFormat();

		// settors
		void setInternalFormat(unsigned intFmt);
		void setImageFormat(unsigned imgFmt);

};
