#pragma once
#include <vector>
#include "Object.h"

// Manages the objects created
class ResourceManager
{
	private:
		std::vector<Object> objectList; // the list of objects

		// removes all zombies from object list
		void killAllZombies();

	public:

		// constructor?

		// add a new object
		void addObject(Object);

		// sets an object to be removed, given its id
		void removeObject(unsigned);

		// get number of objects
		unsigned getNumObjects(void);

		// find object
		int findObject(unsigned);

		// deconstructor?

};