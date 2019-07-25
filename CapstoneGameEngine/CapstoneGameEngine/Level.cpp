#include "Level.h"

// constructor
Level::Level()
{
	isActive = false;
}

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
Object* Level::addObject(Object tempObj)
{
	Object* newObj = new Object(tempObj);

	// push new object to end of the list
	objectList.push_back(newObj);

	// run the on creation update for the new object (if the update function exists)
	updateFunction updatePtr = newObj->getUpdatePtr();

	// don't auto call creation update for levels because levels are created at the start
	// dont' really want multiple levels being created on top of each other
	if (updatePtr != nullptr && newObj->getType() != ObjectType::LEVEL)
	{
		updatePtr(newObj, Update::CREATED);
	}

	return newObj;
}

Object* Level::getObject(std::string name)
{
	// go through elvel and find obejct
	for (int x = 0; objectList.size(); ++x)
	{
		// check if found the object (same name)
		if (!objectList[x]->getName().compare(name))
		{
			return objectList[x];
		}
	}

	// didn't find the object
	return nullptr;
}

std::string Level::getName()
{
	return levelName;
}

bool Level::getActive()
{
	return isActive;
}

void Level::setName(std::string newName)
{
	levelName = newName;
}

void Level::setActive(bool newActiveState)
{
	isActive = newActiveState;
}
