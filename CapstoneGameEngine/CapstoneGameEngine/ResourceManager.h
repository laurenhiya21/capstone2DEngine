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

		// Retrieves the vertex and fragment shader code from file and complie
		Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile);

	public:

		// constructor
		ResourceManager();

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
		Shader LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);

		// Gets a stored shader
		Shader& getShader(std::string name);

		// deconstructor
		~ResourceManager();
};