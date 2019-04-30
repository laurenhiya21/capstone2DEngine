#include <iostream> // cout, endl
#include <sstream> // stringstream
#include <fstream> // ifstream
#include "ResourceManager.h"

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
Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile)
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

	Shader newShader;
	//call shader compile here------------------------------------------------------------

	return newShader;
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
	// while still objects to check, check if object visable
	for (int x = 0; x < objectList.size(); ++x)
	{
		// return position of object if found
		if (objectList[x].getVisable() == true)
		{
			//render here
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
Shader ResourceManager::LoadShader(const char * vShaderFile, const char * fShaderFile, std::string name)
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
		x = addShader(Shader(vShaderFile, fShaderFile, name));
	}

	// load the shader from the file to the correct spot
	shaderList[x] = loadShaderFromFile(vShaderFile, fShaderFile);

	return shaderList[x];
}
