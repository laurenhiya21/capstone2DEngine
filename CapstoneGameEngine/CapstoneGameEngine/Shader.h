#pragma once

#include <string>
#include <glew.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>

// Object to compile and manange the shaders
class Shader
{
	protected:
		static unsigned freeID; // first free ID

	private:
		unsigned ID; // unique ID for the shader
		std::string name; // name of the shader
		
		//not sure if these should be char* or strings-------------------------------------
		// location of the vertex and fragment shader source code
		char* vertexSource;
		char* fragmentSource;

	public:

		// construtcors
		Shader();
		Shader(const char* vSource, const char* fSource, std::string n);

		// gettors
		unsigned getID();
		std::string getName();

		// compiles the shader given the source code
		void compile(const char* vSource, const char* fSource);

};