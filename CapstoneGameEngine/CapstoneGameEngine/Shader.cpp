#include "Shader.h"

unsigned Shader::freeID = 0;

Shader::Shader()
{
	// set the id and set the next free id
	ID = freeID;
	++freeID;
}

unsigned Shader::getID()
{
	return ID;
}

std::string Shader::getName()
{
	return name;
}
