#pragma once

#include <string>

// Object to compile and manange the shaders
class Shader
{
	protected:
		static unsigned freeID; // first free ID

	private:
		unsigned ID; // unique ID for the shader
		std::string name; // name of the shader
		// probably need 3 char* for each shader
		//TO DOOO

	public:

		// construtcor
		Shader();

		// gettors
		unsigned getID();
		std::string getName();

};