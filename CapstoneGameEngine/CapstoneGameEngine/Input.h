#pragma once

#include "HeadHancho.h"

// Handles all the inputs to the game
class Input: public System
{
	private:
		// probably need something for all keyboard keys
		// someting for if keys dealt with
		// mouse postion?
		// similar to keyboard keys but mouse keys?
		// controlelr stuff?
		// time variables?

	public:

		// constructor
		Input();

		// run/update the input system
		void run();

		// deconstrutor
		~Input();
};