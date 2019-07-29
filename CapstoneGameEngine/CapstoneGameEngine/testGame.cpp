#include "TestGame.h"

#include <iostream>
#include "Input.h" // moving player
#include "CoreObjects.h" // text object data

int score = 0; // a player's score for testing
int winScore = 0; // score player needs to win (based on number of otters to collect)

// Collision behaviour between an otter an another object
// assumption that obj1 is an otter
void otterCollision(Object* obj1, Object* obj2)
{
	std::cout << "Collision between Obj ID " << obj1->getID() << " and Obj ID " << obj2->getID() << std::endl;

	// if the otter collided with a player, destroy otter object and increase score
	if (obj2->getType() == ObjectType::PLAYER)
	{
		++score;
		std::cout << "Score is: " << score << std::endl;
		obj1->setZombie(true);
	}
}

// Update behaviour between an otter and another object
// update type can be on creation, run time, or on deletion
void otterUpdate(Object * otter, Update::Type t)
{
	// if an otter was created, add 1 to the needed score to win
	if (t == Update::CREATED)
	{
		++winScore;
	}

	// just to test if the destroy update actually gets called
	if (t == Update::DESTROYED)
	{
		std::cout << "#" << otter->getID() << ": You gots me!" <<  std::endl;
	}
}

// Collision behaviour between an player an another object
// assumption that obj1 is a player
void playerCollision(Object* player, Object * obj2)
{
	// if the player collided with a otter, decrease life and display it
	if (obj2->getType() == ObjectType::OTTER)
	{
		PlayerData* pData = (PlayerData*)player->getObjectDataPtr();
		pData->hp -= 10;

		std::cout << "Total HP: " << pData->hp << std::endl;
	}
}

// Update behaviour between an player and another object
// update type can be on creation, run time, or on deletion
void playerUpdate(Object* player, Update::Type t)
{
	// create the player specfic data
	// this is auto deleted in the Object deconstrucor
	if (t == Update::CREATED)
	{
		PlayerData* pData = new PlayerData;
		pData->hp = 200;
		player->setObjectDataPtr(pData);
	}

	// update the player while it is still not dead
	if (t == Update::UPDATED)
	{
		Input* inputPtr = (Input*)sysHeadHancho.sysList[sysNames::INPUT];

		// If left button was pressed, move player left
		if (inputPtr->getState(Action::LEFT) == KeyState::DOWN)
		{
			//std::cout << "Go left!" << std::endl;
			player->updatePosition(-15, 0);
		}

		// If right button was pressed, move player right
		if (inputPtr->getState(Action::RIGHT) == KeyState::DOWN)
		{
			//std::cout << "Go right!" << std::endl;
			player->updatePosition(15, 0);
		}

		// If up button was pressed, move player up
		if (inputPtr->getState(Action::UP) == KeyState::DOWN)
		{
			//std::cout << "Go up!" << std::endl;
			player->updatePosition(0, -15);
		}

		// If dowbn button was pressed, move player down
		if (inputPtr->getState(Action::DOWN) == KeyState::DOWN)
		{
			//std::cout << "Go down!" << std::endl;
			player->updatePosition(0, 15);
		}

		// temp escape-----------------------------------------------
		if (inputPtr->getState(Action::ESCAPE) == KeyState::DOWN)
		{
			sysHeadHancho.exit();
		}
	}
}

// Update behaviour on text given the type of update
// update type can be on creation, run time, or on deletion
void textUpdate(Object * text, Update::Type t)
{
	// create the text specfic data
	// this is auto deleted in the Object deconstrucor
	if (t == Update::CREATED)
	{
		TextData* tData = new TextData;
		tData->data = "test text";
		text->setObjectDataPtr(tData);
	}

	if (t == Update::UPDATED)
	{
		TextData* tData = (TextData*)text->getObjectDataPtr();

		if (score != winScore)
		{
			tData->data = std::to_string(score);
		}

		else
		{
			tData->data = "Otters are the best! You win";
		}

	}

}

// Update behaviour on level1 given the type of update
// update type can be on creation, run time, or on deletion
void level1Update(Object* level1, Update::Type t)
{
	// add objects to the level on creation
	if (t == Update::CREATED)
	{
		Level* level1Ptr = sysHeadHancho.RManager.addLevel("LEVEL1");
		level1Ptr->setActive(true);

		Object test; //player
		test.setPosition(10, 10);
		test.setSize(20, 20);
		test.setType(ObjectType::PLAYER);
		test.setUpdateFunction(playerUpdate);
		test.setCollisionFunction(playerCollision);
		test.setName("Player");

		Texture playerTexture = sysHeadHancho.RManager.getTexture("player");
		test.setSpriteID(playerTexture.getID());

		level1Ptr->addObject(test);

		// 5 otters for testing

		// first get the texture id (same texture used for all otters)
		Texture otterTexture = sysHeadHancho.RManager.getTexture("otter");
		unsigned otterID = otterTexture.getID();

		Object otter1;
		otter1.setPosition(100, 50);
		otter1.setSize(30, 30);
		otter1.setSpriteID(otterID);
		otter1.setType(ObjectType::OTTER);
		otter1.setCollisionFunction(otterCollision);
		otter1.setUpdateFunction(otterUpdate);
		otter1.setName("Otter1");
		level1Ptr->addObject(otter1);

		Object otter2;
		otter2.setPosition(500, 200);
		otter2.setSize(30, 30);
		otter2.setSpriteID(otterID);
		otter2.setType(ObjectType::OTTER);
		otter2.setCollisionFunction(otterCollision);
		otter2.setUpdateFunction(otterUpdate);
		otter2.setName("Otter2");
		level1Ptr->addObject(otter2);

		Object otter3;
		otter3.setPosition(300, 250);
		otter3.setSize(30, 30);
		otter3.setSpriteID(otterID);
		otter3.setType(ObjectType::OTTER);
		otter3.setCollisionFunction(otterCollision);
		otter3.setUpdateFunction(otterUpdate);
		otter3.setName("Otter3");
		level1Ptr->addObject(otter3);

		Object otter4;
		otter4.setPosition(300, 50);
		otter4.setSize(30, 30);
		otter4.setSpriteID(otterID);
		otter4.setType(ObjectType::OTTER);
		otter4.setCollisionFunction(otterCollision);
		otter4.setUpdateFunction(otterUpdate);
		otter4.setName("Otter4");
		level1Ptr->addObject(otter4);

		Object otter5;
		otter5.setPosition(700, 550);
		otter5.setSize(30, 30);
		otter5.setSpriteID(otterID);
		otter5.setType(ObjectType::OTTER);
		otter5.setCollisionFunction(otterCollision);
		otter5.setUpdateFunction(otterUpdate);
		otter5.setColour(glm::vec3(0.5, 0.8, 0.2));
		otter5.setName("Otter5");
		level1Ptr->addObject(otter5);

		Object testText;
		testText.setPosition(250, 300);
		testText.setSize(1, 1);
		testText.setColour(glm::vec3(0.5, 0.8, 0.2));
		testText.setType(ObjectType::TEXT);
		testText.setUpdateFunction(textUpdate);
		testText.setName("WinText");
		level1Ptr->addObject(testText);
	}

	if (t == Update::UPDATED)
	{
		// tell user won if they got all the otters
		// move onto the next level
		if (score == winScore)
		{
			std::cout << "You win!" << std::endl;
			winScore = 0;
			score = 0;
			level1->getUpdatePtr()(level1, Update::DESTROYED);

			// get the global level to access the level objects (for creating next level)
			Level* globalLvPtr = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL");

			// check if it's valid before using
			// should never get this
			if (globalLvPtr == nullptr)
			{
				std::cout << "Reall bad stuff! Couldn't find global level oh no!" << std::endl;
				return;
			}

			// get the level2 object so that level 2 can be created
			Object* level2Obj = globalLvPtr->getObject("LEVEL2");

			// make sure it was valid
			// should never get this
			if (level2Obj == nullptr)
			{
				std::cout << "Reall bad stuff! Couldn't find level 2 object oh no!" << std::endl;
				return;
			}

			// create level 2 so it can be used
			level2Obj->getUpdatePtr()(level2Obj, Update::CREATED);
		}
	}

	if (t == Update::DESTROYED)
	{
		// get global level ptr to access level 1 ptr
		Level* globalLvPtr = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL");

		// get the level1 object and set it to inactive
		Object* level1Obj = globalLvPtr->getObject("LEVEL1");
		level1Obj->setActive(false);

		sysHeadHancho.RManager.removeLevel("LEVEL1");
	}
}

// Update behaviour on level2 given the type of update
// update type can be on creation, run time, or on deletion
void level2Update(Object* level1, Update::Type t)
{
	// add objects to the level on creation
	if (t == Update::CREATED)
	{
		Level* level2Ptr = sysHeadHancho.RManager.addLevel("LEVEL2");
		level2Ptr->setActive(true);

		Object test; //player
		test.setPosition(10, 10);
		test.setSize(20, 20);
		test.setType(ObjectType::PLAYER);
		test.setUpdateFunction(playerUpdate);
		test.setCollisionFunction(playerCollision);
		test.setName("Player");

		Texture playerTexture = sysHeadHancho.RManager.getTexture("player");
		test.setSpriteID(playerTexture.getID());

		level2Ptr->addObject(test);

		// a few otters for testing
		// first get the texture id (same texture used for all otters)
		Texture otterTexture = sysHeadHancho.RManager.getTexture("otter");
		unsigned otterID = otterTexture.getID();

		Object otter1;
		otter1.setPosition(100, 50);
		otter1.setSize(30, 30);
		otter1.setSpriteID(otterID);
		otter1.setType(ObjectType::OTTER);
		otter1.setCollisionFunction(otterCollision);
		otter1.setUpdateFunction(otterUpdate);
		otter1.setName("Otter1");
		level2Ptr->addObject(otter1);

		Object otter3;
		otter3.setPosition(150, 250);
		otter3.setSize(30, 30);
		otter3.setSpriteID(otterID);
		otter3.setType(ObjectType::OTTER);
		otter3.setCollisionFunction(otterCollision);
		otter3.setUpdateFunction(otterUpdate);
		otter3.setName("Otter3");
		level2Ptr->addObject(otter3);

		Object otter4;
		otter4.setPosition(300, 70);
		otter4.setSize(30, 30);
		otter4.setSpriteID(otterID);
		otter4.setType(ObjectType::OTTER);
		otter4.setCollisionFunction(otterCollision);
		otter4.setUpdateFunction(otterUpdate);
		otter4.setColour(glm::vec3(1, 0, 0));
		otter4.setName("Otter4");
		level2Ptr->addObject(otter4);

		Object otter5;
		otter5.setPosition(700, 550);
		otter5.setSize(30, 30);
		otter5.setSpriteID(otterID);
		otter5.setType(ObjectType::OTTER);
		otter5.setCollisionFunction(otterCollision);
		otter5.setUpdateFunction(otterUpdate);
		otter5.setColour(glm::vec3(0.5, 0.8, 0.2));
		otter5.setName("Otter5");
		level2Ptr->addObject(otter5);

		// text for displaying win/score
		Object testText;
		testText.setPosition(250, 300);
		testText.setSize(1, 1);
		testText.setColour(glm::vec3(0.5, 0.8, 0.2));
		testText.setType(ObjectType::TEXT);
		testText.setUpdateFunction(textUpdate);
		testText.setName("WinText");
		level2Ptr->addObject(testText);

		// collision box to move to space invaders level
		Object spaceInvadersCollision;
		spaceInvadersCollision.setPosition(750, 300);
		spaceInvadersCollision.setSize(30, 70);
		spaceInvadersCollision.setType(ObjectType::TO_SPACE_INVADERS);
		spaceInvadersCollision.setName("ToSpaceInvaders");
		spaceInvadersCollision.setCollisionFunction(toSpaceInvadersCollision);
		
		Texture collisionTexture = sysHeadHancho.RManager.getTexture("collisionBox");
		spaceInvadersCollision.setSpriteID(collisionTexture.getID());

		level2Ptr->addObject(spaceInvadersCollision);
	}

	if (t == Update::DESTROYED)
	{
		// get global level ptr to access level 2 ptr
		Level* globalLvPtr = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL");

		// get the level1 object and set it to inactive
		Object* level2Obj = globalLvPtr->getObject("LEVEL2");
		level2Obj->setActive(false);

		sysHeadHancho.RManager.removeLevel("LEVEL2");
	}
}

// Collision behaviour between the object that transitions to the space invader level 
	// and an another object
// Transitions to the space invaders level when player collides with object
void toSpaceInvadersCollision(Object* collisonObj, Object* obj2)
{
	// only transition to the space invader level if the player collided with it
	if (obj2->getType() == ObjectType::PLAYER)
	{
		std::cout << "Go to space invaders!" << std::endl;

		// get the global level to access the level objects
		// for destorying level 2 and creating next levvel
		Level* globalLvPtr = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL");

		// get the level2 object to level 2 can be destryoed
		Object* level2Obj = globalLvPtr->getObject("LEVEL2");

		// destory level 2
		level2Obj->getUpdatePtr()(level2Obj, Update::DESTROYED);

		// get space invader level
		Object* levelSpaceObj = globalLvPtr->getObject("LEVEL_SPACE_INVADERS");

		// create the space invader level
		levelSpaceObj->getUpdatePtr()(levelSpaceObj, Update::CREATED);
	}
}

// Update behaviour on space invaders level given the type of update
// update type can be on creation, run time, or on deletion
void levelSpaceInvadersUpdate(Object* spaceLevel, Update::Type t)
{
	// add level to list and create objects
	if (t == Update::CREATED)
	{
		Level* levelSpacePtr = sysHeadHancho.RManager.addLevel("LEVEL_SPACE_INVADERS");
		levelSpacePtr->setActive(true);

		// load carrot spaceship
		createCarrot(levelSpacePtr);
	}
}

// Creates the carrot ship with default starting position
// Takes in the level to create it on
void createCarrot(Level* spawnLevel)
{
	Texture carrotTexture = sysHeadHancho.RManager.getTexture("carrot");
	unsigned carrotID = carrotTexture.getID();

	Object carrot;
	carrot.setPosition(300, 550);
	carrot.setSize(20, 40);
	carrot.setSpriteID(carrotID);
	carrot.setType(ObjectType::CARROT);
	//carrot.setCollisionFunction(otterCollision);
	carrot.setUpdateFunction(carrotUpdate);
	carrot.setName("Carrot");
	carrot.setLevelPtr(spawnLevel);
	spawnLevel->addObject(carrot);
}

// Creates a bullet (set to inactive and not visable right now)
// Takes in level to create it on and the type of bullet it is
// Type can be PLAYER_BULLET or ENEMEY_BULLET"
// returns ptr to new bullets
Object* createBullet(Level* spawnLevel, ObjectType::Type bulletType)
{
	// load bullet texture
	Texture bulletTexture = sysHeadHancho.RManager.getTexture("bullet");
	unsigned bulletID = bulletTexture.getID();

	// set parameters same to all bullets
	Object newBullet;
	newBullet.setSize(5, 10);
	newBullet.setSpriteID(bulletID);
	newBullet.setLevelPtr(spawnLevel);

	if (bulletType == ObjectType::PLAYER_BULLET)
	{
		newBullet.setType(ObjectType::PLAYER_BULLET);
		//playerBullet.setCollisionFunction();
		//carrot.setUpdateFunction(otterUpdate);
		newBullet.setName("PlayerBullet");
		newBullet.setColour(glm::vec3(0.3, 0.89, 1)); // blue bullet
	}

	else if (bulletType == ObjectType::ENEMY_BULLET)
	{
		newBullet.setType(ObjectType::ENEMY_BULLET);
		//playerBullet.setCollisionFunction();
		//carrot.setUpdateFunction(otterUpdate);
		newBullet.setName("EnemyBullet");
		newBullet.setColour(glm::vec3(1, 0, 0)); // red bullet
	}

	else
	{
		std::cout << "Oh no! Wrong bullet type??" << std::endl;
		return nullptr;
	}

	// add the bullet to the level and return ptr to it
	return spawnLevel->addObject(newBullet);
}

// Update behaviour on carrot ship given the type of update
// update type can be on creation, run time, or on deletion
void carrotUpdate(Object* carrot, Update::Type t)
{
	// update the carrot while it is still not dead
	// (movement and shooting)
	if (t == Update::UPDATED)
	{
		Input* inputPtr = (Input*)sysHeadHancho.sysList[sysNames::INPUT];

		// If left button was pressed, move player left
		if (inputPtr->getState(Action::LEFT) == KeyState::DOWN)
		{
			carrot->updatePosition(-15, 0);
		}

		// If right button was pressed, move player right
		if (inputPtr->getState(Action::RIGHT) == KeyState::DOWN)
		{
			carrot->updatePosition(15, 0);
		}

		// if space pressed, shoot!
		if (inputPtr->getState(Action::SHOOT) == KeyState::PRESSED)
		{
			// create a bullet and add to level (createBullet adds to level)
			Object* newBullet = createBullet(carrot->getLevelPtr(), ObjectType::PLAYER_BULLET);
			newBullet->setActive(true);
			newBullet->setVisable(true);
			newBullet->setPosition(carrot->getPosition().x, carrot->getPosition().y - 10);
			newBullet->setVelocity(0, -10); // bullet should go straight up
			newBullet->setUpdateFunction(bulletUpdate);
			// set collision function

			std::cout << "SHOOT" << std::endl;
		}

		// temp escape-----------------------------------------------
		if (inputPtr->getState(Action::ESCAPE) == KeyState::DOWN)
		{
			sysHeadHancho.exit();
		}
	}
}

// Update behaviour on a bullet given the type of update
// update type can be on creation, run time, or on deletion
// can handle both enemy and player bullets
void bulletUpdate(Object* bullet, Update::Type t)
{
	if (t == Update::UPDATED)
	{
		// keep bullet moving (get cur position & add velocity to get new position)
		bullet->setPosition(bullet->getPosition().x + bullet->getVelocity().x, bullet->getPosition().y + bullet->getVelocity().y);

		// check to see if bullet is off the screen, and destory if it is
		glm::vec2 newPos = bullet->getPosition();
		unsigned winH = sysHeadHancho.mainWindow.getHeight();
		unsigned winW = sysHeadHancho.mainWindow.getWidth();

		// check all 4 sides of the screen
		if (newPos.x <= 0 || newPos.x >= winW || newPos.y <= 0 || newPos.y >= winH)
		{
			// mark the bullet for destruction if it went off
			bullet->setZombie(true);
		}
	}
}