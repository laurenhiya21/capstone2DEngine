#include "TestGame.h"
#include <iostream>

// a player's score for testing
int score = 0;

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
	if (score == 5)
	{
		std::cout << "You win!" << std::endl;
	}
}
