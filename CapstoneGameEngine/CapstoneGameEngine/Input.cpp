#include "Input.h"
#include <iostream> //TEMP OUTPUT

// constructor
Input::Input()
{
	// add key for ESCAPE
	keyList.push_back(InputKey(GLFW_KEY_ESCAPE, KeyState::UP, Action::ESCAPE));

	// add key for LEFT (A in WASAD)
	keyList.push_back(InputKey(GLFW_KEY_A, KeyState::UP, Action::LEFT));

	// add key for RIGHT (D in WASAD)
	keyList.push_back(InputKey(GLFW_KEY_D, KeyState::UP, Action::RIGHT));

	// add key for UP in (W in WASAD)
	keyList.push_back(InputKey(GLFW_KEY_W, KeyState::UP, Action::UP));

	// add key for DOWN in (S in WASAD)
	keyList.push_back(InputKey(GLFW_KEY_S, KeyState::UP, Action::DOWN));

	// add key for ACCEPT (Enter for now?)
	keyList.push_back(InputKey(GLFW_KEY_ENTER, KeyState::UP, Action::ACCEPT));
}

// add a key to the keyArray
// returns 0 if successful, -1 if already there
// for now just add the key in... maybe be able to add diff default state and action---------------
int Input::addKey(int newKey)
{
	// attempt to find the given newKey
	for (int x = 0; x < keyList.size(); ++x)
	{
		// if the newKey is already in the container, stop
		// don't add it twice
		if (newKey == keyList[x].getKey())
		{
			return -1;
		}
	}

	// if the key was not found in the container, add it
	// temp stuff here??------------------------------------------
	keyList.push_back(InputKey(newKey, KeyState::UP, -1));

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
		if (getState(x) == KeyState::PRESSED)
		{
			keyList[x].setState(KeyState::DOWN);
			continue; // move onto next key
		}

		// if the key's state is currently at released,
		// auto move onto up state (so pressed only ~1 frame)
		else if (getState(x) == KeyState::RELEASED)
		{
			keyList[x].setState(KeyState::UP);
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
			if (getState(x) == KeyState::DOWN)
			{
				keyList[x].setState(KeyState::RELEASED);

				continue; // go to next key
			}
		}

		// if the key is being pressed (key currently DOWN)
		else
		{
			// if the state changed from up to down (key was pressed)
			// change the key's state to pressed
			if (getState(x) == KeyState::UP)
			{
				keyList[x].setState(KeyState::PRESSED);

				continue; // go to next key
			}
		}

		// if the states are the same, no need to do anything
	}

	// TEMP UNTIL GET ABOVE TO WORK YO----------------------------------------------------------
	// want to actually be able to exit the darn thing ha
	if (glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		sysHeadHancho.exit();
		//glfwSetWindowShouldClose(sysHeadHancho.mainWindow.windowPtr, GL_TRUE);
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

// constructor w/ parameters
Input::InputKey::InputKey(int k = -1, int s = KeyState::UP, int a = -1)
{
	key = k;
	state = s;
	keyAction = a;
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
void Input::InputKey::setState(int newState)
{
	state = newState;
}

void Input::InputKey::setAction(int newAction)
{
	keyAction = newAction;
}
