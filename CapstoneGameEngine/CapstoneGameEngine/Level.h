#pragma once
#include <vector>
#include <string>

class Object; // forward declare Object just so it knows it exists

class Level
{
	private:
		std::vector<Object*> objectList; // the list of objects a level owns
		std::string levelName; // name of the level (used to find it)
		bool isActive; // whether the level is active or not

	public:
		// constructor
		Level();

		// get the number of objects in the level
		unsigned getNumObjects();

		// returns an object* given it's position in the objectList
		Object* getObjectByPos(unsigned);

		// remove an object given it's position in the list
		void removeObject(unsigned);

		// add an object to the object list
		Object* addObject(Object tempObj);

		// get an object by its name
		Object* getObject(std::string);

		// gettors
		std::string getName();
		bool getActive();

		// settors
		void setName(std::string);
		void setActive(bool);
};