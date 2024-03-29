#include "Logic.h"
#include "Input.h" // interact with keys that Actions are mapped to
#include "ResourceManager.h" // interact with the Objects (change posisiton, destroy, etc).
#include "TestGame.h" // for assigning collision functions and update functions

// constructor
Logic::Logic()
{
}

bool once = true;

// run/update the logic system
void Logic::run()
{
	// only create the level objects once at start
	if (once)
	{
		createLevelObjects();
		once = false;
	}

	// check for any collisions betwen all Objects
	doCollisions();

	// update the active objects (and kill zombies)
	sysHeadHancho.RManager.updateActiveObjects();
}

// create the level objects, which are used to create, update, and delete the levels
void Logic::createLevelObjects()
{
	// a dummy level that is used to hold the levelObjs
	Level* globalLvPtr = sysHeadHancho.RManager.addLevel("GLOBAL_LEVEL");
	globalLvPtr->setActive(true);

	bool otterTest = false; // TESTING ONLY FOR EARLY LEVELS

	// only do this when testing all levels
	if (otterTest)
	{
		Object level1Obj;
		level1Obj.setType(ObjectType::LEVEL);
		level1Obj.setUpdateFunction(level1Update);
		level1Obj.setVisable(false);
		level1Obj.setName("LEVEL1");

		// only for the first level, call creation update function
		// (don't want multiple levls being created at once)
		Object* level1Ptr = globalLvPtr->addObject(level1Obj);
		level1Ptr->getUpdatePtr()(level1Ptr, Update::CREATED);

		Object level2Obj;
		level2Obj.setType(ObjectType::LEVEL);
		level2Obj.setUpdateFunction(level2Update);
		level2Obj.setVisable(false);
		level2Obj.setName("LEVEL2");
		globalLvPtr->addObject(level2Obj);
	}

	Object spaceStartLevelObj;
	spaceStartLevelObj.setType(ObjectType::LEVEL);
	spaceStartLevelObj.setUpdateFunction(levelSpaceStartUpdate);
	spaceStartLevelObj.setVisable(false);
	spaceStartLevelObj.setName("LEVEL_START_SPACE_INVADERS");
	
	Object* spaceStartPtr = globalLvPtr->addObject(spaceStartLevelObj); // need the object only when not in test

	// if not testing, make first space invader screen the first one
	if (!otterTest)
	{
		// only for the first level, call creation update function
		// (don't want multiple levls being created at once)
		
		spaceStartPtr->getUpdatePtr()(spaceStartPtr, Update::CREATED);
	}

	Object spaceInvadersLevelObj;
	spaceInvadersLevelObj.setType(ObjectType::LEVEL);
	spaceInvadersLevelObj.setUpdateFunction(levelSpaceInvadersUpdate);
	spaceInvadersLevelObj.setVisable(false);
	spaceInvadersLevelObj.setName("LEVEL_SPACE_INVADERS");
	globalLvPtr->addObject(spaceInvadersLevelObj);

}

// check for any collisions betwen all Objects
void Logic::doCollisions()
{
	// total number of objects (across all levels) to check
	int totalNumObjects = sysHeadHancho.RManager.getNumObjects();

	// check all objects with the other objects (but try and minimize double checking)
	for (int x = 0; x < totalNumObjects; ++x)
	{
		// get first object to check
		Object* obj1 = sysHeadHancho.RManager.findObjectByPos(x);

		// skip over objects that are no longer there
		// quick fix to avoid checking objects that were in a removed Level
		if (obj1 == nullptr)
		{
			continue;
		}

		for (int y = x; y < totalNumObjects; ++y) // setting y = x to minimizie duplication in checks
		{
			// get object to check against second
			Object* obj2 = sysHeadHancho.RManager.findObjectByPos(y);

			// skip over objects that are no longer there
			// quick fix to avoid checking objects that were in a removed Level
			if (obj2 == nullptr)
			{
				continue;
			}

			// check the collision between the two objects
			bool isCollision = checkCollision(obj1, obj2);

			// do a thing if there was collision between the objects
			if (isCollision)
			{
				// get the collision functions for each of the two objects
				collisionFunction obj1Collision = obj1->getCollisionPtr();
				collisionFunction obj2Collision = obj2->getCollisionPtr();

				// run each of the two function's collision functions if they exist
				if (obj1Collision != nullptr)
				{
					obj1Collision(obj1, obj2);
				}

				if (obj2->getCollisionPtr() != nullptr)
				{
					obj2Collision(obj2, obj1);
				}
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
**	Liscence info:	https://creativecommons.org/licenses/by-nc/4.0/
**	Link to source: https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
**	Modified?: Yes. Added check that two Objects are not the same, 
**			change parameters from two GameObjects (created type from tutorial) 
			to Object (self created type), additional comments added
*************************************************************************/
// check collision between 2 Objects, return true if there was collision, false if none
// Rectangle collision AABB - AABB
bool Logic::checkCollision(Object* obj1, Object* obj2)
{
	// make sure that objects are not the same
	if (obj1->getID() == obj2->getID())
	{
		return false;
	}

	// Is there collision on the x-axis?
	bool collisionX = obj1->getPosition().x + obj1->getSize().x >= obj2->getPosition().x && obj2->getPosition().x + obj2->getSize().x >= obj1->getPosition().x;

	// Is there collision on the y-axis?
	bool collisionY = obj1->getPosition().y + obj1->getSize().y >= obj2->getPosition().y && obj2->getPosition().y + obj2->getSize().y >= obj1->getPosition().y;

	// Collision only if on both axes
	return collisionX && collisionY;
}