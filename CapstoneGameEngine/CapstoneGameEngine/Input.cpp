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
	for (int x = 0; x < keyArray.size; ++x)
	{
		// if the newKey is already in the container, stop
		// don't add it twice
		if (newKey == keyArray[x].getKey())
		{
			return -1;
		}
	}

	// if the key was not found in the container, add it
	keyArray.push_back(InputKey(newKey));

	return 0;
}

// run/update the input system
void Input::run()
{
	// go through all the possible inputs
	for (int x = 0; x < keyArray.size(); ++x)
	{
		// if the key's state is currently at pressed,
		// auto move onto down state (so pressed only ~1 frame)
		if (keyArray[x].getState() == PRESSED)
		{
			keyArray[x].setState(DOWN);
			continue; // move onto next key
		}

		// if the key's state is currently at released,
		// auto move onto up state (so pressed only ~1 frame)
		else if (keyArray[x].getState() == RELEASED)
		{
			keyArray[x].setState(UP);
			continue; // move onto next key
		}

		// get the state key we're checking is currently in according to openGL
		int openGLState = glfwGetKey(sysHeadHancho.mainWindow.windowPtr, keyArray[x].getKey());

		// compare what openGL says key is doing with what key state is at
		// if the key is not being pressed (key currently UP)
		if (openGLState == GLFW_RELEASE)
		{
			// if the state changed from down to up (key was released)
			// change the key's state to released
			if (keyArray[x].getState() == DOWN)
			{
				keyArray[x].setState(RELEASED);

				continue; // go to next key
			}
		}

		// if the key is being pressed (key currently DOWN)
		else
		{
			// if the state changed from up to down (key was pressed)
			// change the key's state to pressed
			if (keyArray[x].getState() == UP)
			{
				keyArray[x].setState(PRESSED);

				continue; // go to next key
			}
		}

		// if the states are the same, no need to do anything
	}

	//--------------------------------------------------------------------------------

	//std::cout << "Space" << glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_SPACE) << std::endl;

	// mostly from old stuff cause simple and it's TEMPPPPPP----------------------------------------------
	if (glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		sysHeadHancho.exit();
		//glfwSetWindowShouldClose(sysHeadHancho.mainWindow.windowPtr, GL_TRUE);
	}

	if (glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_W) == GLFW_PRESS)
	{
		std::cout << "W Pressed!" << std::endl;
	}

	if (glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_S) == GLFW_PRESS)
	{
		std::cout << "S Pressed!" << std::endl;
	}

	if (glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_A) == GLFW_PRESS)
	{
		std::cout << "A Pressed!" << std::endl;
	}

	if (glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_D) == GLFW_PRESS)
	{
		std::cout << "D Pressed!" << std::endl;
	}
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

// get the keystate of the key
KeyState Input::InputKey::getState()
{
	return state;
}

// get what the key is
int Input::InputKey::getKey()
{
	return key;
}
// settors----
void Input::InputKey::setState(KeyState newState)
{
	state = newState;
}
