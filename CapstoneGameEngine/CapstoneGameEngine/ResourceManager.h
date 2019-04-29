#pragma once
#include <vector>
#include <string>

#include "Object.h"
#include "Shader.h"

// Manages the objects created
class ResourceManager
{
	private:
		std::vector<Object> objectList; // the list of objects
		std::vector<Shader> shaderList; // the list of shaders

		// removes all zombies from object list
		void killAllZombies();

		// Loads and generates a vertex, fragment, and (optionally) geometry shader from file
		Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);

	public:

		// constructor?

		// add a new object/shader
		void addObject(Object newObj);
		unsigned addShader(Shader newShad);

		// sets an object to be removed, given its id
		void removeObject(unsigned);

		// get number of objects
		unsigned getNumObjects(void);

		// find object
		int findObject(unsigned);

		// render all the visable objects
		void renderVisable();

		// updates all objects that need to be updated
		// including killing zombies
		void updateActiveObjects();

		// Loads a shader from a vertex and fragment shader's code, 
		// also can load geometry shader if not null
		Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);

		// deconstructor?

};