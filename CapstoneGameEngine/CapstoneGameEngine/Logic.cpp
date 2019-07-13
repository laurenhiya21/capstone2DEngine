#include "Logic.h"
#include "Input.h" // interact with keys that Actions are mapped to
#include "ResourceManager.h" // interact with the Objects (change posisiton, destroy, etc).
#include "TestGame.h" // for assigning collision functions and update functions

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
}

// create the player object
void Logic::createPlayer()
{
	// just add an object with default values? let's seeee---------------------------
	Object test;
	test.setPosition(10, 10);
	test.setSize(20, 20);
	test.setSpriteID(1);
	test.setType(ObjectType::PLAYER);
	test.setUpdateFunction(playerUpdate);
	test.setCollisionFunction(playerCollision);
	sysHeadHancho.RManager.addObject(test);

	// 5 otters for testing
	Object otter1;
	otter1.setPosition(100, 50);
	otter1.setSize(30, 30);
	otter1.setSpriteID(2);
	otter1.setType(ObjectType::OTTER);
	otter1.setCollisionFunction(otterCollision);
	otter1.setUpdateFunction(otterUpdate);
	sysHeadHancho.RManager.addObject(otter1);

	Object otter2;
	otter2.setPosition(500, 200);
	otter2.setSize(30, 30);
	otter2.setSpriteID(2);
	otter2.setType(ObjectType::OTTER);
	otter2.setCollisionFunction(otterCollision);
	otter2.setUpdateFunction(otterUpdate);
	sysHeadHancho.RManager.addObject(otter2);

	Object otter3;
	otter3.setPosition(300, 250);
	otter3.setSize(30, 30);
	otter3.setSpriteID(2);
	otter3.setType(ObjectType::OTTER);
	otter3.setCollisionFunction(otterCollision);
	otter3.setUpdateFunction(otterUpdate);
	sysHeadHancho.RManager.addObject(otter3);

	Object otter4;
	otter4.setPosition(300, 50);
	otter4.setSize(30, 30);
	otter4.setSpriteID(2);
	otter4.setType(ObjectType::OTTER);
	otter4.setCollisionFunction(otterCollision);
	otter4.setUpdateFunction(otterUpdate);
	sysHeadHancho.RManager.addObject(otter4);

	Object otter5;
	otter5.setPosition(700, 550);
	otter5.setSize(30, 30);
	otter5.setSpriteID(2);
	otter5.setType(ObjectType::OTTER);
	otter5.setCollisionFunction(otterCollision);
	otter5.setUpdateFunction(otterUpdate);
	otter5.setColour(glm::vec3(0.5, 0.8, 0.2));
	sysHeadHancho.RManager.addObject(otter5);

	//
	//tRender->renderText("test text!", 250.0f, 300.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));

	Object testText;
	testText.setPosition(250, 300);
	testText.setSize(1, 1);
	testText.setColour(glm::vec3(0.5, 0.8, 0.2));
	testText.setType(ObjectType::TEXT);
	testText.setUpdateFunction(textUpdate);
	sysHeadHancho.RManager.addObject(testText);
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
			bool isCollision = checkCollision(obj1, obj2);

			// do a thing if there was collision between the objects--------------------------------------
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