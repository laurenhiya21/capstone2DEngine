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

	keyList.push_back(InputKey(GLFW_KEY_R, KeyState::UP, Action::DOWN));

	// add key for ACCEPT (Enter for now?)
	keyList.push_back(InputKey(GLFW_KEY_ENTER, KeyState::UP, Action::ACCEPT));
}

// add a key to the keyList
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
	keyList.push_back(InputKey(newKey, KeyState::UP, -1));

	return 0;
}

// run/update the input system
void Input::run()
{
	// go through all the possible inputs
	for (int x = 0; x < keyList.size(); ++x)
	{
		int curState = keyList[x].getState();

		// if the key's state is currently at pressed,
		// auto move onto down state (so pressed only ~1 frame)
		if (curState == KeyState::PRESSED)
		{
			keyList[x].setState(KeyState::DOWN);
			continue; // move onto next key
		}

		// if the key's state is currently at released,
		// auto move onto up state (so pressed only ~1 frame)
		else if (curState == KeyState::RELEASED)
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
			if (curState == KeyState::DOWN)
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
			if (curState == KeyState::UP)
			{
				keyList[x].setState(KeyState::PRESSED);

				continue; // go to next key
			}
		}

		// if the states are the same, no need to do anything
	}
}

// get the state of given action
// return -1 if invalid key passed
int Input::getState(int stateToGet)
{
	int state = KeyState::UP;

	// go through all of the keys, find the action we want and get the state
	// DOWN has highest priority so automatically quit the loop if
	// any one of the action's states is DOWN (can have multiple keys set to one action)
	for (int x = 0; x < keyList.size(); ++x)
	{
		// skip actions that don't match the action we are looking for
		if (keyList[x].getAction() != stateToGet)
		{
			continue;
		}

		// get the state of tha current keybind
		int newState = keyList[x].getState();

		// update the state of the action if it's DOWN
		// or if it's a different state at all
		if (newState > state || newState == KeyState::DOWN)
		{
			state = newState;
		}

		// if the action is down, we can return early
		// since DOWN is most important
		if (state == KeyState::DOWN)
		{
			break;
		}
	}

	//return the state
	return state;
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
