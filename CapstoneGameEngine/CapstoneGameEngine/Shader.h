#pragma once

#include <string>
#include <glew.h>
#include <glm/glm.hpp> //matrix stuff
#include <glm/gtc/type_ptr.hpp> //mat4 ptr stuff?--------------------

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

		// sets current shader as active
		Shader& use();

		// compiles the shader given the source code
		void compile(const char* vSource, const char* fSource);

		//-----------------??
		void setInteger(const char* n, float value, bool useShader = false);
		void setMatrix4(const char* n, const glm::mat4& matrix, bool useShader = false);

};