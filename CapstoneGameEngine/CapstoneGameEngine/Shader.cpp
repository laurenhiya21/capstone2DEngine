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

// compiles the shader given the source code
void Shader::compile(const char * vSource, const char * fSource)
{
	int sVertex, sFragment;

	// setup vertex shader
	sVertex = glCreateShader(GL_VERTEX_SHADER); //neeed to figure iout how to properl;y include glew------------------------
	glShaderSource(sVertex, 1, &vSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");

	// setup fragment shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");

	// hook shaders into the program
	//this->ID = glCreateProgram();---------------might not need to do this?
	glAttachShader(ID, sVertex);
	glAttachShader(ID, sFragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	// deleted uneeded created shaders, as they are linked to program now
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
}
