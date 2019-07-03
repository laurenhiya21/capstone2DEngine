#include "Logic.h"
#include "Input.h" // interact with keys that Actions are mapped to
#include "ResourceManager.h" // interact with the Objects (change posisiton, destroy, etc).

// constructor
// just needs to set the triggers
// don't think triggers need to be set during runtime so just set at beginning for now?
Logic::Logic()
{
	// all of them are going to be PRESSED for now but could be DOWN or something else later

	// set trigger for ESCAPE
	triggers[Action::ESCAPE] = KeyState::PRESSED;

	// set trigger for LEFT
	triggers[Action::LEFT] = KeyState::DOWN;

	// set trigger for RIGHT
	triggers[Action::RIGHT] = KeyState::DOWN;

	// set trigger for UP
	triggers[Action::UP] = KeyState::DOWN;

	// set trigger for DOWN
	triggers[Action::DOWN] = KeyState::DOWN;

	// set trigger for ACCEPT
	triggers[Action::ACCEPT] = KeyState::PRESSED;

	// don't set a trigger for total cause it should be referenced except for loops
}

bool once = true;

// run/update the logic system
void Logic::run()
{
	// only create the player once at start
	if (once)
	{
		createPlayer();
		once = false;
	}

	// check for any collisions betwen all Objects
	doCollisions();

	// update the active objects (and kill zombies)
	sysHeadHancho.RManager.updateActiveObjects();

	// check if any actions need to be run and run if necessary
	checkActions();
}

// create the player object
void Logic::createPlayer()
{
	// just add an object with default values? let's seeee---------------------------
	Object test;
	test.setPosition(10, 10);
	test.setSize(20, 20);
	test.setSpriteID(1);
	sysHeadHancho.RManager.addObject(test); // this sets ID to 0 for some reason/???-------------------

	// another test Obj?
	Object test2;
	test2.setPosition(100, 50);
	test2.setSize(30, 30);
	test2.setSpriteID(2);
	sysHeadHancho.RManager.addObject(test2);
}

// check for any collisions betwen all Objects
void Logic::doCollisions()
{
	// total number of objects to check
	int totalNumObjects = sysHeadHancho.RManager.getNumObjects();

	// check all objects with the other objects (but try and minimize double checking)
	for (int x = 0; x < totalNumObjects; ++x)
	{
		// get first object to check
		Object* obj1 = sysHeadHancho.RManager.findObjectByPos(x);

		for (int y = x; y < totalNumObjects; ++y) // setting y = x to minimizie duplication in checks
		{
			// get object to check against second
			Object* obj2 = sysHeadHancho.RManager.findObjectByPos(y);

			// check the collision between the two objects
			bool isCollision = checkCollision(*obj1, *obj2);

			// do a thing if there was collision between the objects--------------------------------------
			if (isCollision)
			{
				std::cout << "Collision between Obj ID " << obj1->getID() << " and Obj ID " << obj2->getID() << std::endl;
			}
		}
	}

}

// check collision between 2 Objects, return true if there was collision, false if none
// Rectangle collision AABB - AABB
bool Logic::checkCollision(Object& obj1, Object& obj2)
{
	// make sure that objects are not the same
	if (obj1.getID() == obj2.getID())
	{
		return false;
	}

	// Is there collision on the x-axis?
	bool collisionX = obj1.getPosition().x + obj1.getSize().x >= obj2.getPosition().x && obj2.getPosition().x + obj2.getSize().x >= obj1.getPosition().x;

	// Is there collision on the y-axis?
	bool collisionY = obj1.getPosition().y + obj1.getSize().y >= obj2.getPosition().y && obj2.getPosition().y + obj2.getSize().y >= obj1.getPosition().y;

	// Collision only if on both axes
	return collisionX && collisionY;
}

// get trigger for a specified action
// -1 if invalid trigger
int Logic::getTrigger(int triggerToGet)
{
	// make sure that input is for a valid action
	if (triggerToGet < 0 || triggerToGet >= Action::TOTAL)
	{
		return -1;
	}

	return triggers[triggerToGet];
}
// checks which actions needs to be run and runs them
void Logic::checkActions()
{
	// check all the actions
	for (int x = 0; x < Action::TOTAL; ++x)
	{
		// get the input system to get the states of the action keys
		Input* inputPtr = (Input*)sysHeadHancho.sysList[sysNames::INPUT];

		// get key state for action
		int curKeyState = inputPtr->getState(x);

		// check if key state matches trigger state
		// run action if it matches
		if (curKeyState == getTrigger(x))
		{
			runAction(x);
		}

		// don't do anything if action should not be run
	}
}

// run actions that have met their trigger
void Logic::runAction(int actionToRun)
{
	Object* tempPlayer = sysHeadHancho.RManager.findObject(0); // kind of temp yo-----------------------------------------

	// run the action
	switch (actionToRun)
	{
		case Action::LEFT:
			std::cout << "Go left!" << std::endl;

			// temp moving
			// get character
			tempPlayer->updatePosition(-15, 0);
			break;

		case Action::RIGHT:
			std::cout << "Go right!" << std::endl;

			// temp moving
			// get character
			tempPlayer->updatePosition(15, 0);
			break;

		case Action::UP:
			std::cout << "Go up!" << std::endl;

			// temp moving
			// get character
			tempPlayer->updatePosition(0, -15);
			break;

		case Action::DOWN:
			std::cout << "Go down!" << std::endl;

			// temp moving
			// get character
			tempPlayer->updatePosition(0, 15);
			break;

		case Action::ACCEPT:
			std::cout << "Accept!" << std::endl;
			break;

		case Action::ESCAPE:
			sysHeadHancho.exit();
			break;
	}
}
