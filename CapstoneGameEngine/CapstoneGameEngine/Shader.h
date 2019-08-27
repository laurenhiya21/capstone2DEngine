#pragma once

#include <iostream> // cout erors
#include <string>
#include "Graphics.h"

// Object to compile and manange the shaders
class Shader
{
	protected:
		static unsigned freeID; // first free ID

	private:
		unsigned ID; // unique ID for the shader
		std::string name; // name of the shader

		int makeShader(GLenum shaderType, const char * source); // make the shader given source code

	public:

		// construtcors
		Shader();
		Shader(std::string n);

		// gettors
		unsigned getID();
		std::string getName();

		// sets current shader as active
		Shader& use();

		// compiles the shader given the source code
		void compile(const char* vSource, const char* fSource);

		// checks the shader for compile errors
		void Shader::checkCompileErrors(int object, std::string type);

		//-----------------??
		void setInteger(const char* n, float value, bool useShader = false);
		void SetVector3f(const char* n, const glm::vec3 &value, bool useShader = false);
		void setMatrix4(const char* n, const glm::mat4& matrix, bool useShader = false);

};