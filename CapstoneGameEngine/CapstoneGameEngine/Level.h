#pragma once
#include <vector>
#include "Object.h"

class Level
{
	private:
		std::vector<Object*> objectList; // the list of objects a level owns

	public:
		// get the number of objects in the level
		unsigned getNumObjects();

		// returns an object* given it's position in the objectList
		Object* getObjectByPos(unsigned);

		// remove an object given it's position in the list
		void removeObject(unsigned);

		// add an object to the object list
		void addObject(Object tempObj);

		// load needed for the objects for the level
		void load();

		// check if the trigger for another level was triggered

		// mark all objects used as zombies to move onto another level
		void unload();
};