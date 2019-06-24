#include "Input.h"
#include <iostream> //TEMP OUTPUT

// constructor
Input::Input()
{
}

// add a key to the keyArray
// returns 0 if successful, -1 if already there
// for now just add the key in... maybe be able to add diff default state and action---------------
int Input::addKey(int newKey)
{
	// attempt to find the given newKey
	for (int x = 0; x < keyList.size; ++x)
	{
		// if the newKey is already in the container, stop
		// don't add it twice
		if (newKey == keyList[x].getKey())
		{
			return -1;
		}
	}

	// if the key was not found in the container, add it
	keyList.push_back(InputKey(newKey));

	return 0;
}

// run/update the input system
void Input::run()
{
	// go through all the possible inputs
	for (int x = 0; x < keyList.size(); ++x)
	{
		// if the key's state is currently at pressed,
		// auto move onto down state (so pressed only ~1 frame)
		if (getState(x) == PRESSED)
		{
			keyList[x].setState(DOWN);
			continue; // move onto next key
		}

		// if the key's state is currently at released,
		// auto move onto up state (so pressed only ~1 frame)
		else if (getState(x) == RELEASED)
		{
			keyList[x].setState(UP);
			continue; // move onto next key
		}

		// get the state key we're checking is currently in according to openGL
		int openGLState = glfwGetKey(sysHeadHancho.mainWindow.windowPtr, keyList[x].getKey());

		// compare what openGL says key is doing with what key state is at
		// if the key is not being pressed (key currently UP)
		if (openGLState == GLFW_RELEASE)
		{
			// if the state changed from down to up (key was released)
			// change the key's state to released
			if (getState(x) == DOWN)
			{
				keyList[x].setState(RELEASED);

				continue; // go to next key
			}
		}

		// if the key is being pressed (key currently DOWN)
		else
		{
			// if the state changed from up to down (key was pressed)
			// change the key's state to pressed
			if (getState(x) == UP)
			{
				keyList[x].setState(PRESSED);

				continue; // go to next key
			}
		}

		// if the states are the same, no need to do anything
	}
}

// get the state of given key
// return -1 if invalid key passed
int Input::getState(int stateToGet)
{
	// check if it's a valid key to get the state of
	if (stateToGet < 0 || stateToGet >= keyList.size())
	{
		return -1;
	}

	return keyList[stateToGet].getState();
}

int Input::getAction(int actionToGet)
{
	// check if it's a valid key to get the state of
	if (actionToGet < 0 || actionToGet >= keyList.size())
	{
		return -1;
	}

	return keyList[actionToGet].getAction();
}

// deconstructor
Input::~Input()
{

}

//---------------------InputKey functions--------------------------------------------------

// constructor w/ parameter
Input::InputKey::InputKey(int k = -1)
{
	key = k;
	state = UP;
}

// get what the key is
int Input::InputKey::getKey()
{
	return key;
}
int Input::InputKey::getState()
{
	return state;
}
int Input::InputKey::getAction()
{
	return keyAction;
}
// settors----
void Input::InputKey::setState(KeyState newState)
{
	state = newState;
}

void Input::InputKey::setAction(int newAction)
{
	keyAction = newAction;
}
