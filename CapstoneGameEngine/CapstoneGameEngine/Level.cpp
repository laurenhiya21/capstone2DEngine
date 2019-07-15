#include "Level.h"

// get the number of objects in the level
unsigned Level::getNumObjects()
{
	return objectList.size();
}

// returns an object* given it's position in the objectList
Object* Level::getObjectByPos(unsigned pos)
{
	// make sure that the object pos is in bounds
	if (pos >= objectList.size())
	{
		return nullptr;
	}

	return objectList[pos];
}

// remove an object given it's position in the list
void Level::removeObject(unsigned pos)
{
	// make sure given position is in bounds
	if (pos >= objectList.size())
	{
		return;
	}

	// if the object is valid, remove the object form the list
	objectList.erase(objectList.begin() + pos);
}

// add an object to the manager
void Level::addObject(Object tempObj)
{
	Object* newObj = new Object(tempObj);

	// push new object to end of the list
	objectList.push_back(newObj);

	// run the on creation update for the new object (if the update function exists)
	updateFunction updatePtr = newObj->getUpdatePtr();

	if (updatePtr != nullptr)
	{
		updatePtr(newObj, Update::CREATED);
	}
}