#include <iostream> // cout, endl
#include <sstream> // stringstream
#include <fstream> // ifstream
#include <SOIL.h> // load image files
#include <Windows.h> // finding files
#include "ResourceManager.h"
#include "HeadHancho.h"
#include "Graphics.h"

// constructor
ResourceManager::ResourceManager()
{
}

// removes all zombies from all of the levels (private function)
void ResourceManager::killAllZombies()
{
	// while there are still levels to check, go through them
	for (int curLevelPos = 0; curLevelPos < levelList.size(); ++curLevelPos)
	{
		// while still objects to check, check if object needs to be removed
		for (int curObjPos = 0; curObjPos < levelList[curLevelPos]->getNumObjects(); ++curObjPos)
		{
			// get the current object
			Object* curObj = levelList[curLevelPos]->getObjectByPos(curObjPos);

			// check if curObj is a zombie
			if (curObj->getZombie() == true)
			{
				// get the curObj's update function
				updateFunction updatePtr = curObj->getUpdatePtr();

				// if it exists, run the update on obj destruction
				if (updatePtr != nullptr)
				{
					updatePtr(curObj, Update::DESTROYED);
				}

				// remove the object from the list
				levelList[curLevelPos]->removeObject(curObjPos);
			}
		}
	}
}
/************************************************************************
**	This code is part of the Learn OpenGL Breakout tutorial
**	It is free to redistribute and/or modify under the
**	CC BY-NC 4.0 license as published by Creative Commons.
**
**	Original Author: Joey de Vries (@JoeyDeVriez)
**	Licence info:	https://creativecommons.org/licenses/by-nc/4.0/
**	Link to source: https://learnopengl.com/In-Practice/2D-Game/Setting-up
**	Modified?: Removed option for loading geometry shader,
		Added position so shader can be compiled without having to return it
*************************************************************************/
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

/************************************************************************
**	This code is part of the Learn OpenGL Breakout tutorial
**	It is free to redistribute and/or modify under the
**	CC BY-NC 4.0 license as published by Creative Commons.
**
**	Original Author: Joey de Vries (@JoeyDeVriez)
**	Licence info:	https://creativecommons.org/licenses/by-nc/4.0/
**	Link to source: https://learnopengl.com/In-Practice/2D-Game/Setting-up
**	Modified?: Minor edits to have function work with naming convention
*************************************************************************/
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

// adds a new level to the level list and returns a ptr to the level added
Level* ResourceManager::addLevel(std::string name)
{
	Level* newLevel = new Level;
	newLevel->setName(name);

	// push new level to the end of the list
	levelList.push_back(newLevel);

	// return ptr of newly added level (not multi-thread safe!)
	return newLevel;
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

// removes a level, given its name
void ResourceManager::removeLevel(std::string name)
{
	// go through the level list while there are still levels to check
	for (int x = 0; x < levelList.size(); ++x)
	{
		// remove from levelList if names match
		// names should be unique so stop if level found
		if (!levelList[x]->getName().compare(name))
		{
			delete levelList[x];
			levelList.erase(levelList.begin() + x);
			return;
		}
	}
}

// get number of objects across all levels
unsigned ResourceManager::getNumObjects(void)
{
	// holds the number of objects across all of the levels
	unsigned numObjects = 0;

	// go through all of the levels and count the number of objects in each
	for (int x = 0; x < levelList.size(); ++x)
	{
		numObjects += levelList[x]->getNumObjects();
	}

	return numObjects;
}

// find an object based on it's id
Object* ResourceManager::findObject(unsigned objID)
{
	// go through all of the levels, while there aer still levels to check
	for (int curLevelPos = 0; curLevelPos < levelList.size(); ++curLevelPos)
	{
		// go through all objects in the level and check their id
		for (int curObjPos = 0; curObjPos < levelList[curLevelPos]->getNumObjects(); ++curObjPos)
		{
			// get the current object we are checking
			Object* curObj = levelList[curLevelPos]->getObjectByPos(curObjPos);

			// return the Object* if the id matches what we are looking for
			if (curObj->getID() == objID)
			{
				return curObj;
			}
		}
	}

	// object was not found
	return nullptr;
}

Level* ResourceManager::getLevel(std::string name)
{
	// go through the levels until it is found
	for (int x = 0; levelList.size(); ++x)
	{
		// check if names are the same
		if (!levelList[x]->getName().compare(name))
		{
			return levelList[x];
		}
	}

	// level not found
	return nullptr;
}

// find object given its position in vector, return Object*
Object* ResourceManager::findObjectByPos(unsigned pos)
{
	// make sure given position is valid
	if (pos >= sysHeadHancho.RManager.getNumObjects())
	{
		return nullptr;
	}

	unsigned numObjects = 0; // to figure out how many objects we've come across so far
	unsigned prevNumObjects = 0; // the number of objects in the levels before the cur one
	unsigned curLevel = 0; // level that object is in
	unsigned objPos = 0; // to figure out the position of the object in the level

	// if spot is valid, figure out which level is is for
	for (; curLevel < levelList.size(); ++curLevel)
	{
		// add the objects in the current level to the counter
		numObjects += levelList[curLevel]->getNumObjects();

		// if the position is < the numObjects encountered
		// then the object with that position must be in that level
		if (pos < numObjects)
		{
			// get the position of the object in the level

			// if the object wasn't on the 0th level
			// need to adjust position (since pos resets for each lvl)
			if (curLevel != 0)
			{
				objPos = pos - prevNumObjects;
			}

			// if the object was on the first level, don't need to change anything
			else
			{
				objPos = pos;
			}

			break;
		}

		// keep track of the previous number tottal objects
		prevNumObjects = numObjects;
	}

	// return the object that was found
	return levelList[curLevel]->getObjectByPos(objPos);
}

// render all the visable objects
void ResourceManager::renderVisable()
{
	// get the graphics sytstem to draw the objects
	Graphics* graphicsPtr = (Graphics*)sysHeadHancho.sysList[sysNames::GRAPHICS];

	// go through all of the levels
	for (int curLevelPos = 0; curLevelPos < levelList.size(); ++curLevelPos)
	{
		// make sure that level is actually active before checking its objects
		if (levelList[curLevelPos]->getActive() == false)
		{
			continue;
		}

		// go through all of the objects in the current level
		for (int curObjPos = 0; curObjPos < levelList[curLevelPos]->getNumObjects(); ++curObjPos)
		{
			// get the curObj
			Object* curObj = levelList[curLevelPos]->getObjectByPos(curObjPos);

			// check if object is visable and should be rendered
			if (curObj->getVisable() == true)
			{
				// if it is text, use the special text renderer
				if (curObj->getType() == ObjectType::TEXT)
				{
					graphicsPtr->tRender->renderText(*curObj);
				}

				// otherwise render the object as normal
				else
				{
					graphicsPtr->drawSprite(*curObj);
				}
			}
		}
	}
}

// updates all objects that need to be updated, including killing zombies
void ResourceManager::updateActiveObjects()
{
	// go through all the levels
	for (int curLevelPos = 0; curLevelPos < levelList.size(); ++curLevelPos)
	{
		// make sure that level is actually active before checking its objects
		if (levelList[curLevelPos]->getActive() == false)
		{
			continue;
		}

		// go through all the objects in a level
		for (int curObjPos = 0; curObjPos < levelList[curLevelPos]->getNumObjects(); ++curObjPos)
		{
			// get the current object
			Object* curObj = levelList[curLevelPos]->getObjectByPos(curObjPos);

			// check if object is active (aka it still needs to update)
			if (curObj->getActive() == true)
			{
				// get the update function of the curObj
				updateFunction updatePtr = curObj->getUpdatePtr();

				// if the update function exists, run it
				if (updatePtr != nullptr)
				{
					updatePtr(curObj, Update::UPDATED);
				}
			}
		}
	}

	// kill the zombies for clean up
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
ResourceManager::~ResourceManager()
{

}