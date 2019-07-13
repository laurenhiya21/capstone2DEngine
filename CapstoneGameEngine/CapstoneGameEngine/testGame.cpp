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

	// tell user won if they got all the otters
	if (score == winScore)
	{
		std::cout << "You win!" << std::endl;
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

		// run the action
		if (inputPtr->getState(Action::LEFT) == KeyState::DOWN)
		{
			std::cout << "Go left!" << std::endl;
			// temp moving
			// get character
			player->updatePosition(-15, 0);
		}

		if (inputPtr->getState(Action::RIGHT) == KeyState::DOWN)
		{
			std::cout << "Go right!" << std::endl;

			// temp moving
			// get character
			player->updatePosition(15, 0);
		}

		if (inputPtr->getState(Action::UP) == KeyState::DOWN)
		{
			std::cout << "Go up!" << std::endl;

			// temp moving
			// get character
			player->updatePosition(0, -15);
		}

		if (inputPtr->getState(Action::DOWN) == KeyState::DOWN)
		{
			std::cout << "Go down!" << std::endl;

			// temp moving
			// get character
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
