#include "Shader.h"

unsigned Shader::freeID = 0;

// constructors---------------------------------------------------------------------
Shader::Shader()
{
	// set the id and set the next free id
	ID = freeID;
	++freeID;

	// initlize the shader sources
	vertexSource = nullptr;
	fragmentSource = nullptr;
}

Shader::Shader(const char* vSource, const char* fSource, std::string n)
{
	// set the id and set the next free id
	ID = freeID;
	++freeID;

	std::strcpy(vertexSource, vSource);
	std::strcpy(fragmentSource, fSource);
	name = n;
}

unsigned Shader::getID()
{
	return ID;
}

std::string Shader::getName()
{
	return name;
}
