#include <iostream> // cout, endl
#include <sstream> // stringstream
#include <fstream> // ifstream
#include "ResourceManager.h"
#include "HeadHancho.h"
#include "Graphics.h"

// constructor
// might not need this for later but using to add objects for testing!------------------
ResourceManager::ResourceManager()
{
	// just add an object with default values? let's seeee---------------------------

	Object test;
	test.setPosition(10,10);
	test.setSize(20, 20);
	addObject(test);
}

// removes all zombies from object list (private function)
void ResourceManager::killAllZombies()
{
	// while still objects to check, check if object needs to be removed
	for (int x = 0; x < objectList.size(); ++x)
	{
		// return position of object if found
		if (objectList[x].getZombie() == true)
		{
			// remove the object from the list
			objectList.erase(objectList.begin() + x);
		}		
	}
}

// Retrieves the vertex and fragment shader code from file and complie
void ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, unsigned position)
{
	// the source code from the file for the shaders
	std::string vertexCode;
	std::string fragmentCode;

	// try to open the files given
	try
	{
		// open the files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;

		// read file contents
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		// close the files
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// convert streams into strings
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}

	// if cannot open the file(s)
	catch (std::exception e)
	{
		std::cout << "ERROR SHADER: Shader files could not be read" << std::endl;
	}

	// create a shader object given the shader code
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// create the shader object from source code
	shaderList[position].compile(vShaderCode, fShaderCode);
}

// add an object to the manager
void ResourceManager::addObject(Object newObj)
{
	// push new object to end of the list
	objectList.push_back(newObj);
}

// add a new shader to the manager, returns position of shader
unsigned ResourceManager::addShader(Shader newShad)
{
	// push new shader to the end of the list
	shaderList.push_back(newShad);

	// return the position of the newly added shader (not multi-thread safe!)
	return shaderList.size() - 1;
}

// adds a new texture to the texture list
unsigned ResourceManager::addTexture(Texture newText)
{
	// push new texture to the end of the list
	textureList.push_back(newText);

	// return the position of the newly added texture (not multi-thread safe!)
	return textureList.size() - 1;
}

// makes an object to be removed, given its id
void ResourceManager::removeObject(unsigned objID)
{
	// find the object in the list (spot in vector)
	int x = findObject(objID);

	// if object was not found, don't do anything else
	if (x == -1)
		return;

	// set the object to be removed
	objectList[x].setZombie(true);
}

// get number of objects
unsigned ResourceManager::getNumObjects(void)
{
	return objectList.size();
}

// find an object based on it's id
int ResourceManager::findObject(unsigned objID)
{
	// while still objects to check, check if found object
	for (int x = 0; x < objectList.size(); ++x)
	{
		// return position of object if found
		if (objectList[x].getID() == objID)
			return x;
	}

	// object was not found
	return -1;
}

// render all the visable objects
void ResourceManager::renderVisable()
{
	// get the graphics sytstem to draw the objects
	Graphics* graphicsPtr = (Graphics*)sysHeadHancho.sysList[sysNames::GRAPHICS];

	// while still objects to check, check if object visable
	for (int x = 0; x < objectList.size(); ++x)
	{
		// check if object is visable and actually should be rendereed
		if (objectList[x].getVisable() == true)
		{
			//render the object
			graphicsPtr->drawSprite(objectList[x]);
		}
			
	}
}

// updates all objects that need to be updated, including killing zombies
void ResourceManager::updateActiveObjects()
{
	// go through all the objects
	for (int x = 0; x < objectList.size(); ++x)
	{
		// check if active
		if (objectList[x].getActive() == true)
		{
			// update here
		}

	}

	// kill the zombies
	killAllZombies();
}

// Loads a shader from a vertex and fragment shader's code, 
// if shader isn't already in the shader list, add it to the list
Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name)
{
	int x = 0;
	bool found = false; // if the shader was found in the shaderlist

	// find the shader from the shader list
	for (; x < shaderList.size(); ++x)
	{
		// check if correct shader
		if (shaderList[x].getName() == name)
		{
			// correct shader was found so stop
			found = true;
			break;
		}
	}

	// if the shader was not found in the list, add it to the list
	if (!found)
	{
		// add the shader
		x = addShader(Shader(name));
	}

	// load the shader from the file to the correct spot
	loadShaderFromFile(vShaderFile, fShaderFile, x);

	return shaderList[x];
}

// Gets a stored shader
Shader& ResourceManager::getShader(std::string name)
{
	// find the shader from the shader list
	for (int x = 0; x < shaderList.size(); ++x)
	{
		// check if correct shader
		if (!shaderList[x].getName().compare(name))
		{
			return shaderList[x];
		}
	}

	// couldn't find so just return first shader
	return shaderList[0];
}

// Get a stored texture from the list
Texture& ResourceManager::getTexture(std::string name)
{
	// find the texture from the texture list
	for (int x = 0; x < textureList.size(); ++x)
	{
		// check if correct shader
		if (!textureList[x].getName().compare(name))
		{
			return textureList[x];
		}
	}

	// couldn't find so just return first shader
	return textureList[0];
}

// deconstructor
// not sure if need/want yet to delete objects here? unsure--------------------------
ResourceManager::~ResourceManager()
{

}
