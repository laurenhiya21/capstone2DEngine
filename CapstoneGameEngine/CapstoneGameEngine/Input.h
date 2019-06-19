#pragma once

#include "HeadHancho.h"
#include <vector> // used to contain keys + their states/actions

// states that any key on the keyboard can be in
enum KeyState
{
	UP,
	PRESSED,
	DOWN,
	RELEASED
};

// Handles all the inputs to the game
class Input: public System
{
	private:
		// container for state of keyboard key 
		// and action associated with it
		class InputKey
		{
			KeyState state; // state of the key (up, pressed, down, released)
			int key; // int that corrosponds to the GLFW keyboard define
			//action here
		};
		
		std::vector<KeyState> keyArray; // list of the keys used

		// someting for if keys dealt with
		// mouse postion?
		// similar to keyboard keys but mouse keys?
		// controlelr stuff?

	public:

		// constructor
		Input();

		// run/update the input system
		void run();

		// deconstrutor
		~Input();
};