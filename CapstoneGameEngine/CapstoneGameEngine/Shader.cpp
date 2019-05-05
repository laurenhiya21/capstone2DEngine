#include "Shader.h"

unsigned Shader::freeID = 0;

// constructors---------------------------------------------------------------------
Shader::Shader()
{
	// set the id and set the next free id
	ID = freeID;
	++freeID;

	// initlize the shader sources
}

Shader::Shader(std::string n)
{
	// set the id and set the next free id
	ID = freeID;
	++freeID;

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

// sets current shader as active
Shader& Shader::use()
{
	glUseProgram(ID);
	return *this;
}

// compiles the shader given the source code
void Shader::compile(const char * vSource, const char * fSource)
{
	int sVertex, sFragment;

	// setup vertex shader
	sVertex = makeShader(GL_VERTEX_SHADER, vSource);
	checkCompileErrors(sVertex, "VERTEX");

	// setup fragment shader
	sFragment = makeShader(GL_FRAGMENT_SHADER, fSource);
	checkCompileErrors(sFragment, "FRAGMENT");

	// hook shaders into the program
	ID = glCreateProgram();
	glAttachShader(ID, sVertex);
	glAttachShader(ID, sFragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	// deleted uneeded created shaders, as they are linked to program now
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
}

// checks the shader for compile errors
void Shader::checkCompileErrors(int object, std::string type)
{
	int success;
	char infoLog[1024]; // will contain compliation info if not success

	// if we are checking a fragment or vertex shader
	if (type != "PROGRAM")
	{
		// bleh comments, success is changed here though
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			// get the info log of what error was
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "ERROR SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -------------------------------------------------------"
				<< std::endl;
		}
	}

	// if was program that we're checking
	else
	{
		// bleh comments, success is changed here though
		glGetShaderiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			// get the info log of what error was
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "ERROR SHADER: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -------------------------------------------------------"
				<< std::endl;
		}
	}

}

// comments are hard???==============--------------------------------------------------------------------

void Shader::setInteger(const char * n, float value, bool useShader)
{
	if (useShader)
		use();
	glUniform1i(glGetUniformLocation(ID, n), value);
}

void Shader::setMatrix4(const char * n, const glm::mat4 & matrix, bool useShader)
{
	if (useShader)
		use();
	glUniformMatrix4fv(glGetUniformLocation(ID, n), 1, GL_FALSE, glm::value_ptr(matrix));
}

// make the shader given the source code
int Shader::makeShader(GLenum shaderType, const char* source)
{
	int shaderID = glCreateShader(shaderType);

	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);

	return shaderID;

}
