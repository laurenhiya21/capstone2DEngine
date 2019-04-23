#pragma once
#include <vector>
#include "Object.h"

// Manages the objects created
class ResourceManager
{
	private:
		std::vector<Object> objectList; // the list of objects

	public:

		// constructor?

		// add a new object
		void addObject(Object);

		// remove an object
		void removeObject(unsigned);

		// get number of objects
		unsigned getNumObjects(void);

		// find object
		int findObject(unsigned);

		// deconstructor?

};