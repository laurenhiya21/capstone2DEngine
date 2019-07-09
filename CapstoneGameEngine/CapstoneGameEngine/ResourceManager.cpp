#include <iostream> // cout, endl
#include <sstream> // stringstream
#include <fstream> // ifstream
#include <SOIL.h> // load image files
#include <Windows.h> // finding files
#include "ResourceManager.h"
#include "HeadHancho.h"
#include "Graphics.h"

// constructor
// might not need this for later but using to add objects for testing!------------------
ResourceManager::ResourceManager()
{
}

// removes all zombies from object list (private function)
void ResourceManager::killAllZombies()
{
	// while still objects to check, check if object needs to be removed
	for (unsigned x = 0; x < objectList.size(); ++x)
	{
		// return position of object if found
		if (objectList[x].getZombie() == true)
		{
			// run the Object's on deletion update function (if it has one)
			updateFunction updatePtr = objectList[x].getUpdatePtr();

			if (updatePtr != nullptr)
			{
				updatePtr(&objectList[x], Update::DESTROYED);
			}

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

// retrive texture from the file
void ResourceManager::loadTextureFromFile(const char * file, bool alpha, unsigned position)
{
	// if there is transparency, set the correct formats
	if (alpha)
	{
		textureList[position].setInternalFormat(GL_RGBA);
		textureList[position].setImageFormat(GL_RGBA);
	}

	// load the image for the texture
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, textureList[position].getImageFormat() == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

	// generate the texture
	textureList[position].generate(width, height, image);

	// free image data
	SOIL_free_image_data(image);

}

// attempts to find the shader, if not, adds to the shaderList
// returns the position of the shader
unsigned ResourceManager::addOrFindShader(std::string name)
{
	unsigned x = 0;
	bool found = false; // if the shader was found in the shaderlist

						// find the shader from the shader list
	for (; x < shaderList.size(); ++x)
	{
		// check if correct shader
		if (!shaderList[x].getName().compare(name))
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

	return x;
}

// add an object to the manager
void ResourceManager::addObject(Object newObj)
{
	// push new object to end of the list
	objectList.push_back(newObj);

	// run the on creation update for the new object (if the update function exists)
	updateFunction updatePtr = objectList.back().getUpdatePtr();

	if (updatePtr != nullptr)
	{
		updatePtr(&newObj, Update::CREATED);
	}
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
	Object* temp = findObject(objID);

	// if object was not found, don't do anything else
	if (temp == nullptr)
		return;

	// set the object to be removed
	temp->setZombie(true);
}

// get number of objects
unsigned ResourceManager::getNumObjects(void)
{
	return objectList.size();
}

// find an object based on it's id
Object* ResourceManager::findObject(unsigned objID)
{
	// while still objects to check, check if found object
	for (unsigned x = 0; x < objectList.size(); ++x)
	{
		// return position of object if found
		if (objectList[x].getID() == objID)
			return &objectList[x];
	}

	// object was not found
	return nullptr;
}

// find object given its position in vector, return Object*
Object* ResourceManager::findObjectByPos(unsigned pos)
{
	// make sure given position is in bounds
	if (pos >= objectList.size())
	{
		return nullptr;
	}

	// if spot is valid, return the Object*
	return &objectList[pos];
}

// render all the visable objects
void ResourceManager::renderVisable()
{
	// get the graphics sytstem to draw the objects
	Graphics* graphicsPtr = (Graphics*)sysHeadHancho.sysList[sysNames::GRAPHICS];

	// while still objects to check, check if object visable
	for (unsigned x = 0; x < objectList.size(); ++x)
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
	for (unsigned x = 0; x < objectList.size(); ++x)
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
	int x = addOrFindShader(name);

	// load the shader from the file to the correct spot
	loadShaderFromFile(vShaderFile, fShaderFile, x);

	return shaderList[x];
}

// Loads a texture (and adds to list if not there) from a file
// texture needs to associate with an object so it also needs to find the object
Texture ResourceManager::loadTexture(const char * file, bool alpha, std::string name)
{
	unsigned x = 0;
	bool found = false; // if texture was foudn in texturelist

	// go through the list and find the texure
	for (; x < textureList.size(); ++x)
	{
		// check if correct texture
		if (!textureList[x].getName().compare(name))
		{
			found = true;
			break;
		}
	}

	// if the texure was not foundin hte list, add it in
	if (!found)
	{
		x = addTexture(Texture(name));
	}

	// load the texture from the file to the correct texture
	loadTextureFromFile(file, alpha, x);
	
	return textureList[x];
}

// loads all textures from the texture folder
void ResourceManager::loadAllTextures()
{
	// to get the name of the sprite files
	WIN32_FIND_DATA spriteFile;

	// gets the first file from where the textures are stored
	HANDLE fileHandle = FindFirstFile("../assets/*", &spriteFile);

	std::string fileType(".png");

	// go through the folder until all files have been checked
	do
	{
		// get a string version of the file name
		std::string spriteFileName(spriteFile.cFileName);

		// if the length of the file type is longer than the whole file name, file not what we want
		// example: if file was a.h (len 3), it obviously can't be a .png (len 4) file
		if (spriteFileName.length() < fileType.length())
			continue;

		// seperate out the name of the file and the file's extension
		std::string spriteName = spriteFileName.substr(0, spriteFileName.length() - fileType.length());
		std::string fileExt = spriteFileName.substr(spriteName.length(), fileType.length());

		//if its not a .png file, then it's not a texture
		if (fileExt.compare(fileType))
			continue;

		// file is something to be loaded at this point, so put together what we need to load
		// (path + filename)
		std::string spriteToLoad = "../assets/" + spriteFileName;

		// load the texture, using the name of the file as the name of the texture
		loadTexture(spriteToLoad.c_str(), GL_TRUE, spriteName.c_str());

	} while (FindNextFile(fileHandle, &spriteFile));

}

// Gets a stored shader
Shader& ResourceManager::getShader(std::string name)
{
	// find the shader from the shader list
	for (unsigned x = 0; x < shaderList.size(); ++x)
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
	for (unsigned x = 0; x < textureList.size(); ++x)
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

