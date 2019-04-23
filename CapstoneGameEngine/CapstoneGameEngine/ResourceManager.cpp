#include "ResourceManager.h"

// add an object to the manager
void ResourceManager::addObject(Object newObj)
{
	// push new object to end of the list
	objectList.push_back(newObj);
}

// remove an object
void ResourceManager::removeObject(unsigned objID)
{
	// find the object in the list (spot in vector)
	int x = findObject(objID);

	// if object was not found, don't do anything else
	if (x == -1)
		return;

	// remove the object from the list
	objectList.erase(objectList.begin() + x);
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
