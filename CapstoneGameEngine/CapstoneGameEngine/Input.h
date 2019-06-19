#pragma once

#include "HeadHancho.h"
#include <vector> // used to contain keys + their states/actions

// states that any key on the keyboard can be in
// UP = key not being pressed down
// PRESSED = change in state from UP to DOWN
// DOWN = key is being pressed down
// PRESSED = change in state from DOWN to UP
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
			private:
				int key; // int that corrosponds to the GLFW keyboard define
				KeyState state; // state of the key (up, pressed, down, released)
				//action here

			public:

				// constructor w/ parameter (defaily state == UP for now..)------------------------
				InputKey(int k);

				// gettors
				KeyState getState();
				int getKey();

				// settors
				void setState(KeyState newState);
		};
		
		std::vector<InputKey> keyArray; // list of the keys used

		// someting for if keys dealt with
		// mouse postion?
		// similar to keyboard keys but mouse keys?
		// controlelr stuff?

	public:

		// constructor
		Input();

		// add a key to the keyArray
		// returns 0 if successful, -1 if already there
		// for now just add the key in... maybe be able to add diff default state and action---------------
		int addKey(int newKey);

		// run/update the input system
		void run();

		// deconstrutor
		~Input();
};