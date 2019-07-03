#pragma once
#include <vector>
#include <string>

#include "Object.h"
#include "Shader.h"
#include "Texture.h"

// Manages the objects created
class ResourceManager
{
	private:
		std::vector<Object> objectList; // the list of objects
		std::vector<Shader> shaderList; // the list of shaders
		std::vector<Texture> textureList; // the list of textures

		// removes all zombies from object list
		void killAllZombies();

		// Retrieves the vertex and fragment shader code from file and complie
		void loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, unsigned position);

		// retrive texture from the file
		void loadTextureFromFile(const char* file, bool alpha, unsigned position);

		// attempts to find the shader, if not, adds to the shaderList
		// returns the position of the shader
		unsigned addOrFindShader(std::string name);

	public:

		// constructor
		ResourceManager();

		// add a new object/shader/texture
		void addObject(Object newObj);
		unsigned addShader(Shader newShad); // returns position of added shader
		unsigned addTexture(Texture newText); 

		// sets an object to be removed, given its id
		void removeObject(unsigned);

		// get number of objects
		unsigned getNumObjects(void);

		// find object given its ID, returns Object*
		Object* findObject(unsigned);

		// find object given its position in vector, return Object*
		Object* findObjectByPos(unsigned);

		// render all the visable objects
		void renderVisable();

		// updates all objects that need to be updated
		// including killing zombies
		void updateActiveObjects();

		// Loads a shader (and add to list if not there) from a vertex and fragment shader's code, ------------------------------------
		Shader LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);

		// Loads a texture (and adds to list if not there) from a file
		Texture loadTexture(const char* file, bool alpha, std::string name);

		// loads all textures from the texture folder
		void loadAllTextures();

		// Gets a stored shader/texure
		Shader& getShader(std::string name);
		Texture& getTexture(std::string name);

		// deconstructor
		~ResourceManager();
};
