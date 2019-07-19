#include "Texture.h"

// constructor with default paramaters
Texture::Texture(std::string n, unsigned w, unsigned h, unsigned intFmt, unsigned imgFmt, unsigned ws, unsigned wt, unsigned filtMin, unsigned filtMax)
{
	name = n;
	width = w;
	height = h;
	internalFmt = intFmt;
	imageFmt = imgFmt;
	wrapS = ws;
	wrapT = wt;
	filterMin = filtMin;
	filterMax = filtMax;

	// generates the texture on the openGl side and sets the id
	glGenTextures(1, &ID);
}

/************************************************************************
**	This code is part of the Learn OpenGL Breakout tutorial
**	It is free to redistribute and/or modify under the
**	CC BY-NC 4.0 license as published by Creative Commons.
**
**	Original Author: Joey de Vries (@JoeyDeVriez)
**	Licence info:	https://creativecommons.org/licenses/by-nc/4.0/
**	Link to source: https://learnopengl.com/In-Practice/2D-Game/Rendering-Sprites
**	Modified?: Only minor edits to the width and height to match convention I use
*************************************************************************/
// generates texture from image data
void Texture::generate(unsigned w, unsigned h, unsigned char * data)
{
	width = w;
	height = h;

	// start binding the texture
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFmt, width, height, 0, imageFmt, GL_UNSIGNED_BYTE, data);

	// Set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);

	// Stop binding the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

// binds the texture as the cuurent opengl texture object
void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

//--------------Gettors---------------------------------------------------------------------------------

unsigned Texture::getID()
{
	return ID;
}

std::string Texture::getName()
{
	return name;
}

unsigned Texture::getImageFormat()
{
	return imageFmt;
}

//--------------Settors---------------------------------------------------------------------------------

void Texture::setInternalFormat(unsigned intFmt)
{
	internalFmt = intFmt;
}

void Texture::setImageFormat(unsigned imgFmt)
{
	imageFmt = imgFmt;
}
