#include "TestGame.h"

#include <iostream>
#include <stdlib.h> // random enemy fire
#include <ctime> // enemy firing time
#include "Input.h" // moving player
#include "CoreObjects.h" // text object data
#include <chrono>

int score = 0; // a player's score for testing
int winScore = 0; // score player needs to win (based on number of otters to collect)

int invadersScore = 0; // score during space invaders

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
				return;
			}

			// get the level2 object so that level 2 can be created
			Object* level2Obj = globalLvPtr->getObject("LEVEL2");

			// make sure it was valid
			// should never get this
			if (level2Obj == nullptr)
			{
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
		// get the global level to access the level objects
		// for destorying level 2 and creating next levvel
		Level* globalLvPtr = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL");

		// get the level2 object to level 2 can be destryoed
		Object* level2Obj = globalLvPtr->getObject("LEVEL2");

		// destory level 2
		level2Obj->getUpdatePtr()(level2Obj, Update::DESTROYED);

		// get space invader start level
		Object* levelSpaceStartObj = globalLvPtr->getObject("LEVEL_START_SPACE_INVADERS");

		// create the space invader start level
		levelSpaceStartObj->getUpdatePtr()(levelSpaceStartObj, Update::CREATED);
	}
}

// Update behaviour on space invaders start screen level given the type of update
// update type can be on creation, run time, or on deletion
void levelSpaceStartUpdate(Object* startLevel, Update::Type t)
{
	if (t == Update::CREATED)
	{
		// add the level
		Level* levelStartPtr = sysHeadHancho.RManager.addLevel("LEVEL_START_SPACE_INVADERS");
		levelStartPtr->setActive(true);

		// create the info text for directions
		Object infoText;
		infoText.setPosition(250, 30);
		infoText.setSize(1, 1);
		infoText.setColour(glm::vec3(1, 1, 1));
		infoText.setType(ObjectType::TEXT);
		infoText.setName("InfoText");
		infoText.setUpdateFunction(infoTextUpdate);
		levelStartPtr->addObject(infoText);

		// create the info text for controls
		Object controlText;
		controlText.setPosition(100, 50);
		controlText.setSize(1, 1);
		controlText.setColour(glm::vec3(1, 1, 1));
		controlText.setType(ObjectType::TEXT);
		controlText.setName("ControlText");
		controlText.setUpdateFunction(controlTextUpdate);
		levelStartPtr->addObject(controlText);
	}

	if (t == Update::UPDATED)
	{
		// move onto the proper space invaders level
		// when accept pushed
		Input* inputPtr = (Input*)sysHeadHancho.sysList[sysNames::INPUT];

		if (inputPtr->getState(Action::ACCEPT) == KeyState::PRESSED)
		{
			// get the global level to access the level objects
			// for destorying start level and creating next levvel
			Level* globalLvPtr = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL");

			// destory the start level
			startLevel->getUpdatePtr()(startLevel, Update::DESTROYED);

			// get the space inadver lv object
			Object* levelSpaceObj = globalLvPtr->getObject("LEVEL_SPACE_INVADERS");

			// create the space invader level
			levelSpaceObj->getUpdatePtr()(levelSpaceObj, Update::CREATED);
		}
	}

	if (t == Update::DESTROYED)
	{
		// get global level ptr to access level 2 ptr
		Level* globalLvPtr = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL");

		// get the level1 object and set it to inactive
		Object* levelStartObj = globalLvPtr->getObject("LEVEL_START_SPACE_INVADERS");
		levelStartObj->setActive(false);

		sysHeadHancho.RManager.removeLevel("LEVEL_START_SPACE_INVADERS");
	}

}

// Update behaviour on start text given the type of update
// update type can be on creation, run time, or on deletion
void infoTextUpdate(Object* infoText, Update::Type t)
{
	// create the text specfic data
	// this is auto deleted in the Object deconstrucor
	if (t == Update::CREATED)
	{
		TextData* tData = new TextData;
		tData->data = "Press space to start!";
		infoText->setObjectDataPtr(tData);
	}
}

// Update behaviour on control text given the type of update
// update type can be on creation, run time, or on deletion
void controlTextUpdate(Object* controlText, Update::Type t)
{
	// create the text specfic data
	// this is auto deleted in the Object deconstrucor
	if (t == Update::CREATED)
	{
		TextData* tData = new TextData;
		tData->data = "Controls: Left/Right (A/D), Shoot (Space)";
		controlText->setObjectDataPtr(tData);
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

		// set score to 0
		invadersScore = 0;

		// create and initliaze the level data
		SpaceInvaderLevelData* levelData = new SpaceInvaderLevelData;
		levelData->totalEnemies = 0; // how many total enemies currently
		levelData->fireInterval = 1; // how often a bullet is fired (secs)
		levelData->timeSinceLastFire = std::time(0); // get current time
		levelData->moveInterval = 1; // how often enemies should move (secs)
		levelData->enemyVelocity = 40; // amount enemies should move after eacf interval
		levelData->timeSinceLastMove = std::time(0); // get current time
		levelData->enemiesMoveRight = true; // enemies start by moving right
		levelData->runGame = true; // set flag to run game
		levelData->wonGame = true; // set won to default
		levelData->startLives = 3;
		levelData->curLives = levelData->startLives; // start off the game with the start num of lives
		spaceLevel->setObjectDataPtr(levelData);

		// load carrot spaceship
		createCarrot(levelSpacePtr);

		// load the enemies
		createAllEnemies(levelSpacePtr);

		// create score text
		// text for displaying win/score
		Object scoreText;
		scoreText.setPosition(250, 10);
		scoreText.setSize(1, 1);
		scoreText.setColour(glm::vec3(1, 1, 1));
		scoreText.setType(ObjectType::TEXT);
		scoreText.setUpdateFunction(scoreUpdate);
		scoreText.setName("ScoreText");
		levelSpacePtr->addObject(scoreText);

		// create restart text
		// displaying restart information
		Object restartText;
		restartText.setPosition(250, 30);
		restartText.setSize(1, 1);
		restartText.setColour(glm::vec3(1, 1, 1));
		restartText.setType(ObjectType::TEXT);
		restartText.setUpdateFunction(restartTextUpdate);
		restartText.setName("RestartText");
		restartText.setVisable(false);
		levelSpacePtr->addObject(restartText);

		// create lives text
		// text for displaying how many lives player has
		Object livesText;
		livesText.setPosition(100, 10);
		livesText.setSize(1, 1);
		livesText.setColour(glm::vec3(1, 1, 1));
		livesText.setType(ObjectType::TEXT);
		livesText.setUpdateFunction(livesTextUpdate);
		livesText.setName("LivesText");
		levelSpacePtr->addObject(livesText);

	}

	if (t == Update::UPDATED)
	{
		// get access to input so we can check if need to exit
		Input* inputPtr = (Input*)sysHeadHancho.sysList[sysNames::INPUT];

		// escape the engine if escape key pressed
		if (inputPtr->getState(Action::ESCAPE) == KeyState::DOWN)
		{
			sysHeadHancho.exit();
		}

		// check to see if an enemy should fire or not
		// data which has the time since the last enemy fire
		Object* spaceLvObj = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL")->getObject("LEVEL_SPACE_INVADERS");
		SpaceInvaderLevelData* spaceLvData = (SpaceInvaderLevelData*)spaceLvObj->getObjectDataPtr();

		// don't access the level data if it doesn't exist
		if (spaceLvData == nullptr)
		{
			return;
		}

		// don't bother firing if the game is over, but check if user pressed r to restart
		if (spaceLvData->runGame == false)
		{
			// restart the level if the game ended and player said to restart
			if (inputPtr->getState(Action::RESTART) == KeyState::PRESSED)
			{
				// if the player has no lives left or they won (no enemies), restart the whole game
				if (spaceLvData->totalEnemies == 0 || spaceLvData->curLives < 1)
				{
					// destroy main space invaders level
					spaceLvObj->getUpdatePtr()(spaceLvObj, Update::DESTROYED);
					
					// get global level ptr to acess space start level
					Level* globalLvPtr = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL");

					// get space invader start level
					Object* levelSpaceStartObj = globalLvPtr->getObject("LEVEL_START_SPACE_INVADERS");

					// create the space invader start level to restart the game
					levelSpaceStartObj->getUpdatePtr()(levelSpaceStartObj, Update::CREATED);

					// we need it to be active
					levelSpaceStartObj->setActive(true);
				}

				// restart movment instead if still have lives
				else
				{
					spaceLvData->runGame = true;
				}
			}

			return;
		}

		// if there are no more enemies, stop the game (don't move non-existant enemies)
		if (spaceLvData->totalEnemies == 0)
		{
			spaceLvData->runGame = false;
			spaceLvData->wonGame = true;
			return;
		}

		// get currrent time
		time_t curTime = std::time(0);
		
		// if there has been enough time since the last fire (according to time interval)
		// have an enemy fire a bullet
		if ((curTime - spaceLvData->timeSinceLastFire) >= spaceLvData->fireInterval)
		{
			// get level for moving enemies and firing bullets
			Level* spaceLvPtr = sysHeadHancho.RManager.getLevel("LEVEL_SPACE_INVADERS");

			// itlitilzae rnd seed (for enemy firing)
			srand(std::time(0));

			// get rnd enemy to fire from (0 to # enemies -1)
			unsigned enemyToGet = (rand() % (spaceLvPtr->getNumObjects() - 1));
			Object* enemyToFire = getNthEnemy(spaceLvPtr, enemyToGet);

			// make sure there actually was an enemy to fire
			if (enemyToFire != nullptr)
			{
				// create the bullet
				Object* newBullet = createBullet(spaceLvPtr, ObjectType::ENEMY_BULLET);

				// set the bullet position to come out approx center and front of the enemy
				newBullet->setPosition(enemyToFire->getPosition().x + 
					(enemyToFire->getSize().x/2), enemyToFire->getPosition().y + (enemyToFire->getSize().y));

				// reset the fire time
				spaceLvData->timeSinceLastFire = std::time(0);
			}
		}

		curTime = std::time(0); // get current time

		// if there has been enough time since the last enemy movement (according to time interval)
		// move all enemies
		if ((curTime - spaceLvData->timeSinceLastMove) >= spaceLvData->moveInterval)
		{
			// get level for moving enemies and firing bullets
			Level* spaceLvPtr = sysHeadHancho.RManager.getLevel("LEVEL_SPACE_INVADERS");

			moveEnemiesCheck(spaceLvPtr);

			// reset move time
			spaceLvData->timeSinceLastMove = std::time(0);
		}
	} // end of update

	if (t == Update::DESTROYED)
	{
		// get the level object so it can be removed (don't set inactive since no next level)
		Object* spaceLvObj = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL")->getObject("LEVEL_SPACE_INVADERS");

		sysHeadHancho.RManager.removeLevel("LEVEL_SPACE_INVADERS");
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
	carrot.setUpdateFunction(carrotUpdate);
	carrot.setCollisionFunction(carrotCollision);
	carrot.setName("Carrot");
	carrot.setLevelPtr(spawnLevel);
	spawnLevel->addObject(carrot);
}

// Creates an enemy
// Takes in level to create it on
void createEnemy(Level* spawnLevel, unsigned posX, unsigned posY)
{
	Texture foxTexture = sysHeadHancho.RManager.getTexture("fox");
	unsigned foxID = foxTexture.getID();

	Object fox;
	fox.setPosition(posX, posY);
	fox.setSize(40, 40);
	fox.setSpriteID(foxID);
	fox.setType(ObjectType::ENEMY);
	fox.setCollisionFunction(enemyCollision);
	fox.setUpdateFunction(enemyUpdate);
	fox.setName("Fox");
	fox.setLevelPtr(spawnLevel);
	spawnLevel->addObject(fox);

	// get the spaceInvadersLevel obj and incriment total num enemies in level
	Object* spaceLvObj = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL")->getObject("LEVEL_SPACE_INVADERS");
	SpaceInvaderLevelData* spaceLvData = (SpaceInvaderLevelData*)spaceLvObj->getObjectDataPtr();
	++spaceLvData->totalEnemies;
}

// get the nth enemy on given level, where n is a number between 0 and totalNum-1 of enemies
// returns ptr to the chosen enemy (nullptr if none)
// if given num is >= totalNum of enemies, returns the last enemy
Object* getNthEnemy(Level* enemyLv, unsigned n)
{
	int currentEnemyNum = -1; // which nth enemy we're at (-1 = haven't checked any, 0th is first)
	Object* curObject; // current object we're checking
	Object* curEnemy = nullptr; // current enemy we're storing

	// go through all the objects in the level until out of objects
	// or we've gotten the nth enemy
	for (int x = 0; x < enemyLv->getNumObjects(); ++x)
	{
		// get the current object
		curObject = enemyLv->getObjectByPos(x);

		// if the current object is an enemy
		// store it and increase num of enemies we've checked
		if (curObject->getType() == ObjectType::ENEMY)
		{
			++currentEnemyNum;
			curEnemy = curObject;

			// stop looking for enemies if we're at the right one
			if (currentEnemyNum >= n)
			{
				break;
			}
		}
	}

	return curEnemy;
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
	newBullet.setCollisionFunction(bulletCollision);
	newBullet.setUpdateFunction(bulletUpdate);

	// set player bullet specfics options
	if (bulletType == ObjectType::PLAYER_BULLET)
	{
		newBullet.setVelocity(0, -10); // bullet should go straight up
		newBullet.setType(ObjectType::PLAYER_BULLET);
		newBullet.setName("PlayerBullet");
		newBullet.setColour(glm::vec3(0.3, 0.89, 1)); // blue bullet
	}

	// set enemy bullet specfics options
	else if (bulletType == ObjectType::ENEMY_BULLET)
	{
		newBullet.setVelocity(0, 10); // bullet should go straight down
		newBullet.setType(ObjectType::ENEMY_BULLET);
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
		// get the space level data to check if player can move/shoot
		Object* spaceLvObj = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL")->getObject("LEVEL_SPACE_INVADERS");
		SpaceInvaderLevelData* spaceLvData = (SpaceInvaderLevelData*)spaceLvObj->getObjectDataPtr();

		// if game is paused/waiting for user confirm, don't allow movment or shooting
		if (spaceLvData->runGame == false)
		{
			return;
		}

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

			// set bullet position to come out approx center of carrot top
			newBullet->setPosition(carrot->getPosition().x + (carrot->getSize().x/2), carrot->getPosition().y - 5);
		}
	}
}

// Collision behaviour between an carrot an another object
// assumption that obj1 is the carrot
void carrotCollision(Object* player, Object* obj2)
{
	// if player got hit by an enemy bullet, game over!
	if (obj2->getType() == ObjectType::ENEMY_BULLET)
	{
		// get the space level data to update lives
		Object* spaceLvObj = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL")->getObject("LEVEL_SPACE_INVADERS");
		SpaceInvaderLevelData* spaceLvData = (SpaceInvaderLevelData*)spaceLvObj->getObjectDataPtr();

		// decrease the live count
		if (spaceLvData->curLives > 0)
		{
			--spaceLvData->curLives;
		}

		// stop running the game for now
		spaceLvData->runGame = false;
	}
}

// Creates all enemies in a level
// Creates several enemies in a set number of rows
// Takes in level to create them in
void createAllEnemies(Level* spawnLevel)
{
	int startX = 100; // position of first enemy
	int startY = 50;
	int curX = startX; // position of currenly spawning enemy
	int curY = startY;
	int offsetX = 50; // how much to space enemies X (space between enemies in same row)
	int offsetY = 70; // how much to space enemies Y (space between rows)

	unsigned enemiesCurInRow = 0; // num enemies in cur row
	unsigned enemiesPerRow = 10; // num enemies needed per row
	unsigned curNumRows = 0; // cur number of rows fully spawned
	unsigned totalRows = 3; // total num rows needed

	// keep spawning enemies until all rows have finished spawning
	while (curNumRows < totalRows)
	{
		// spawn an enemy at the cur position
		createEnemy(spawnLevel, curX, curY);
		++enemiesCurInRow;

		// if spawned all enemies needed in row
		// move onto the next row
		if (enemiesCurInRow == enemiesPerRow)
		{
			// add to completed rows
			++curNumRows;

			// adjust cur spawn position to start of next row
			curX = startX;
			curY = startY + (offsetY * curNumRows);

			// reset num enemies
			enemiesCurInRow = 0;
		}

		// if still need to spawn in current row
		else
		{
			// just adjust x position (keep enemy in cur row)
			curX += offsetX;
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

		// get the space level data to get the total num of enemies & win details
		Object* spaceLvObj = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL")->getObject("LEVEL_SPACE_INVADERS");
		SpaceInvaderLevelData* spaceLvData = (SpaceInvaderLevelData*)spaceLvObj->getObjectDataPtr();

		// destory bullets when game is paused
		if (spaceLvData->runGame == false)
		{
			// mark the bullet for destruction if it went off
			bullet->setZombie(true);
		}
		
	}
}

// Collision behaviour between bullet and another object
// assumption that obj1 is a bullet
// could be expanded to handle both enemy and player bullets (currently only works for player bullets)
void bulletCollision(Object* bullet, Object* obj2)
{
	// if player's bullet hit and enemy, destroy bullet
	if (bullet->getType() == ObjectType::PLAYER_BULLET && obj2->getType() == ObjectType::ENEMY)
	{
		bullet->setZombie(true);
	}

	// if enemy bullet hit player, destory bullet
	else if (bullet->getType() == ObjectType::ENEMY_BULLET && obj2->getType() == ObjectType::CARROT)
	{
		// destroy bullet
		bullet->setZombie(true);
	}
}

// Update behaviour on score given the type of update
// update type can be on creation, run time, or on deletion
void scoreUpdate(Object* scoreText, Update::Type t)
{
	// create the text specfic data
	// this is auto deleted in the Object deconstrucor
	if (t == Update::CREATED)
	{
		TextData* tData = new TextData;
		tData->data = "Score: " + std::to_string(invadersScore);
		scoreText->setObjectDataPtr(tData);
	}

	if (t == Update::UPDATED)
	{
		// get the space level data to get the total num of enemies & win details
		Object* spaceLvObj = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL")->getObject("LEVEL_SPACE_INVADERS");
		SpaceInvaderLevelData* spaceLvData = (SpaceInvaderLevelData*)spaceLvObj->getObjectDataPtr();

		// get the score data to update it
		TextData* tData = (TextData*)scoreText->getObjectDataPtr();

		// if game as normal, just display score
		tData->data = "Score " + std::to_string(invadersScore);
	}
}

// get the enemy that is on the outer edge of the group of enemies in the given level
// Returns the enemy on the outermost edge
// Edge can be TOP, RIGHT, BOTTOM, or LEFT
// Returns nullptr if no enemies
Object* getEdgeEnemy(Level* enemyLevel, EnemyEdge::Edge edgeToCheck)
{
	Object* enemyToCheck = nullptr; // get the enemy to check
	Object* previousEnemy = nullptr; // previous enemy we check
	Object* outerEnemy = nullptr; // the outermost enemy

	// go through all objects in the level until there are no more enemies to check
	for (int x = 0; x < enemyLevel->getNumObjects(); ++x)
	{
		// get the enemy to check
		enemyToCheck = getNthEnemy(enemyLevel, x);

		// stop if there are no enemies to check
		if (enemyToCheck == nullptr)
		{
			return nullptr;
		}

		// if the current enemy we're moving is the same as the last enemy we checked
		// that means we ran out of enemies stop checking
		if (previousEnemy != nullptr && enemyToCheck->getID() == previousEnemy->getID())
		{
			break;
		}

		// if no enemy assigned to outer enemy yet
		// auto assign current enemy to it
		if (outerEnemy == nullptr)
		{
			outerEnemy = enemyToCheck;
		}

		// if we're checking the righthand side of the group and cur enemy is closer to right than outer enemy
		// assign curenemy as new outerEnemy
		else if (edgeToCheck == EnemyEdge::RIGHT && enemyToCheck->getPosition().x > outerEnemy->getPosition().x)
		{
			outerEnemy = enemyToCheck;
		}

		// if we're checking the lefthand side of the group and cur enemy is closer to left than outer enemy
		// assign curenemy as new outerEnemy
		else if (edgeToCheck == EnemyEdge::LEFT && enemyToCheck->getPosition().x < outerEnemy->getPosition().x)
		{
			outerEnemy = enemyToCheck;
		}

		// if we're checking the bottom of the group and cur enemy is closer to bottom than outer enemy
		// assign curenemy as new outerEnemy
		else if (edgeToCheck == EnemyEdge::BOTTOM && enemyToCheck->getPosition().y > outerEnemy->getPosition().y)
		{
			outerEnemy = enemyToCheck;
		}

		// if we're checking the top of the group and cur enemy is closer to top than outer enemy
		// assign curenemy as new outerEnemy
		else if (edgeToCheck == EnemyEdge::TOP && enemyToCheck->getPosition().y < outerEnemy->getPosition().y)
		{
			outerEnemy = enemyToCheck;
		}

		// reassign new previous enemy
		previousEnemy = enemyToCheck;
	}

	return outerEnemy;
}

// Move all the enemies in the level by the enemyVelocity (one step per call)
// Moves enemies back and forth across screen while slowly advancing forward
// keeps enemies within bounds of level
void moveEnemiesCheck(Level* enemyLevel)
{
	// get level data
	Object* spaceLvObj = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL")->getObject("LEVEL_SPACE_INVADERS");
	SpaceInvaderLevelData* spaceLvData = (SpaceInvaderLevelData*)spaceLvObj->getObjectDataPtr();

	// dimensions of window to know when we need to change direction
	unsigned winH = sysHeadHancho.mainWindow.getHeight();
	unsigned winW = sysHeadHancho.mainWindow.getWidth();

	// figure out which direction enemies need to move

	// don't do any movement if game should not be running
	if (spaceLvData->runGame == false)
	{
		return;
	}

	// if enemies are supposed to move right
	if (spaceLvData->enemiesMoveRight == true)
	{
		// get the outermost enemy on the right (for checking if go offscreen)
		Object* outerEnemy = getEdgeEnemy(enemyLevel, EnemyEdge::RIGHT);

		// if outerEnemy is null, no enemies exist so stop
		if (outerEnemy == nullptr)
		{
			return;
		}

		// check if enemies would go offscreen before moving right
		// if they would, move down instead and switch enemy movement to left for next time
		// (need to add position, velocity, and size of enemy since position is based on top left corner)
		if (outerEnemy->getPosition().x + spaceLvData->enemyVelocity + outerEnemy->getSize().x > winW)
		{
			// move all enemies down
			moveAllEnemies(enemyLevel, EnemyEdge::BOTTOM);

			// move enemies left next time
			spaceLvData->enemiesMoveRight = false;
		}

		// if enemies would still be in bounds, move them right
		else
		{
			moveAllEnemies(enemyLevel, EnemyEdge::RIGHT);
		}
	}

	// enemies are supposed to move left
	else
	{
		// get the outermost enemy on the left (for checking if go offscreen)
		Object* outerEnemy = getEdgeEnemy(enemyLevel, EnemyEdge::LEFT);

		// if outerEnemy is null, no enemies exist so stop
		if (outerEnemy == nullptr)
		{
			return;
		}

		// check if enemies would go offscreen before moving left
		// if they would, move down instead and switch enemy movement to right for next time
		if (outerEnemy->getPosition().x - spaceLvData->enemyVelocity < 0)
		{
			// move all enemies down
			moveAllEnemies(enemyLevel, EnemyEdge::BOTTOM);

			// move enemies left next time
			spaceLvData->enemiesMoveRight = true;
		}

		// if enemies would still be in bounds, move them left
		else
		{
			moveAllEnemies(enemyLevel, EnemyEdge::LEFT);
		}
	}
}

// Move all the enemies in the level by the enemyVelocity (one step per call)
// EnemyEdge is uesd as a direction to move enemies
// does not check for bounds and is assumed that given movement is valid
void moveAllEnemies(Level* enemyLevel, EnemyEdge::Edge directionToMove)
{
	// get level data
	Object* spaceLvObj = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL")->getObject("LEVEL_SPACE_INVADERS");
	SpaceInvaderLevelData* spaceLvData = (SpaceInvaderLevelData*)spaceLvObj->getObjectDataPtr();

	Object* enemyToMove; // get the enemy to move
	Object* previousEnemy = nullptr; // previous enemy we moved

	// go through all objects in the level until there are no more enemies to move
	for (int x = 0; x < enemyLevel->getNumObjects(); ++x)
	{
		// get the enemy to move (if getting outer enemy passed, this should pass too)
		enemyToMove = getNthEnemy(enemyLevel, x);

		// if the current enemy we're moving is the same as the last enemy we moved
		// that means we ran out of enemies so no more moving
		if (previousEnemy != nullptr && enemyToMove->getID() == previousEnemy->getID())
		{
			return;
		}

		// if enemies need to move right, move them right
		if (directionToMove == EnemyEdge::RIGHT)
		{
			enemyToMove->setPosition(enemyToMove->getPosition().x + 
				spaceLvData->enemyVelocity, enemyToMove->getPosition().y);
		}

		// if enemies need to move left, move them left
		else if (directionToMove == EnemyEdge::LEFT)
		{
			enemyToMove->setPosition(enemyToMove->getPosition().x - 
				spaceLvData->enemyVelocity, enemyToMove->getPosition().y);
		}

		// if enemies need to move down, move them down
		else if (directionToMove == EnemyEdge::BOTTOM)
		{
			enemyToMove->setPosition(enemyToMove->getPosition().x, 
				enemyToMove->getPosition().y + spaceLvData->enemyVelocity);
		}

		// something went wrong?
		else
		{
			std::cout << "Oh no! Invalid direction??" << std::endl;
		}

		// set the moved enemy as the new previous one
		previousEnemy = enemyToMove;
	}
}

// Update behaviour on a enemy given the type of update
// update type can be on creation, run time, or on deletion
void enemyUpdate(Object* enemy, Update::Type t)
{
	if (t == Update::UPDATED)
	{
		// check if enemy has reached the bottom of the screen (same y as player)
		// first get player
		Object* playerObj = sysHeadHancho.RManager.getLevel("LEVEL_SPACE_INVADERS")->getObject("Carrot");

		// if player is already dead, do nothing
		if (playerObj == nullptr)
		{
			return;
		}

		// lose when enemies get past the player
		if (enemy->getPosition().y + enemy->getSize().y > playerObj->getPosition().y)
		{
			// get the level data to set the proper game run flags
			Object* spaceLvObj = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL")->getObject("LEVEL_SPACE_INVADERS");
			SpaceInvaderLevelData* spaceLvData = (SpaceInvaderLevelData*)spaceLvObj->getObjectDataPtr();

			// stop the game and say player lost
			spaceLvData->runGame = false;
			spaceLvData->wonGame = false;

			// set lives to 0 just to double make sure to end the game
			spaceLvData->curLives = 0;
		}
	}

}

// Collision behaviour between an enemy an another object
// assumption that obj1 is an enemy
void enemyCollision(Object* enemy, Object* obj2)
{
	// if enemy was hit by a player bullet, add score and destory it
	if (obj2->getType() == ObjectType::PLAYER_BULLET)
	{
		// add to player score
		invadersScore += 10;

		// set to destroy enemy
		enemy->setZombie(true);

		// decrease count of enemy num
		Object* spaceLvObj = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL")->getObject("LEVEL_SPACE_INVADERS");
		SpaceInvaderLevelData* spaceLvData = (SpaceInvaderLevelData*)spaceLvObj->getObjectDataPtr();
		--spaceLvData->totalEnemies;
	}
}

// Update behaviour on restart text given the type of update
// update type can be on creation, run time, or on deletion
void restartTextUpdate(Object* restartText, Update::Type t)
{
	// create the text specfic data
	// this is auto deleted in the Object deconstrucor
	if (t == Update::CREATED)
	{
		TextData* tData = new TextData;
		tData->data = "Game over! Press R to restart!";
		restartText->setObjectDataPtr(tData);
	}

	if (t == Update::UPDATED)
	{
		// get the space level data to get the level details
		Object* spaceLvObj = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL")->getObject("LEVEL_SPACE_INVADERS");
		SpaceInvaderLevelData* spaceLvData = (SpaceInvaderLevelData*)spaceLvObj->getObjectDataPtr();
		
		// if game has ended, show the text
		if (spaceLvData->runGame == false)
		{
			restartText->setVisable(true);

			// get the lives data to update it
			TextData* tData = (TextData*)restartText->getObjectDataPtr();

			// if player won, display win!
			if (spaceLvData->wonGame == true)
			{
				tData->data = "You won! Press R to restart!";
			}

			// if the player has lives, say got shot text
			else if (spaceLvData->curLives > 0)
			{
				tData->data = "You got shot! Press R to continue!";
			}

			// otherwise it's a game over and need to restart the whole game
			else
			{
				tData->data = "Game over! Press R to restart!";
			}

		}

		// when the game is running, dont show the text
		else
		{
			restartText->setVisable(false);
		}
	}

}

// Update behaviour on lives text given the type of update
// update type can be on creation, run time, or on deletion
void livesTextUpdate(Object* livesText, Update::Type t)
{
	// get the space level data to get the lives details
	Object * spaceLvObj = sysHeadHancho.RManager.getLevel("GLOBAL_LEVEL")->getObject("LEVEL_SPACE_INVADERS");
	SpaceInvaderLevelData* spaceLvData = (SpaceInvaderLevelData*)spaceLvObj->getObjectDataPtr();

	// create the text specfic data
	// this is auto deleted in the Object deconstrucor
	if (t == Update::CREATED)
	{
		TextData* tData = new TextData;
		tData->data = "Lives: " + std::to_string(spaceLvData->curLives);
		livesText->setObjectDataPtr(tData);
	}

	if (t == Update::UPDATED)
	{
		// get the score data to update it
		TextData* tData = (TextData*)livesText->getObjectDataPtr();

		// keep the lives info up to date
		tData->data = "Lives: " + std::to_string(spaceLvData->curLives);
	}
}
