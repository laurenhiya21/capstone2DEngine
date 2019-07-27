#pragma once
#include "HeadHancho.h"

//Forward delcare object
class Object;

// actions that can be done in the game
// each corrospond with an input (keyboard, controller, mouse)
// which is controlled in the Input class
namespace Action
{ 
	enum
	{
		ESCAPE,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		ACCEPT,
		SHOOT,
		TOTAL
	};
}

// deals with the updating of objects (including AI)
class Logic: public System
{
	private:

	public:

		// constructor
		Logic();

		// run/update the logic system
		void run();

		// create the player object
		void createPlayer();

		// check for any collisions betwen all Objects
		void doCollisions();

		// check collision between 2 Objects, return true if there was collision, false if none
		bool checkCollision(Object*, Object*);
};
