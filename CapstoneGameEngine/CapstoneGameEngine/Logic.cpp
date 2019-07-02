#include "Logic.h"
#include "Input.h" // interact with keys that Actions are mapped to
#include "ResourceManager.h" // interact with the Objects (change posisiton, destroy, etc).

// constructor
// just needs to set the triggers
// don't think triggers need to be set during runtime so just set at beginning for now?
Logic::Logic()
{
	// all of them are going to be PRESSED for now but could be DOWN or something else later

	// set trigger for ESCAPE
	triggers[Action::ESCAPE] = KeyState::PRESSED;

	// set trigger for LEFT
	triggers[Action::LEFT] = KeyState::PRESSED;

	// set trigger for RIGHT
	triggers[Action::RIGHT] = KeyState::PRESSED;

	// set trigger for UP
	triggers[Action::UP] = KeyState::PRESSED;

	// set trigger for DOWN
	triggers[Action::DOWN] = KeyState::PRESSED;

	// set trigger for ACCEPT
	triggers[Action::ACCEPT] = KeyState::PRESSED;

	// don't set a trigger for total cause it should be referenced except for loops
}

bool once = true;

// run/update the logic system
void Logic::run()
{
	// only create the player once at start
	if (once)
	{
		createPlayer();
		once = false;
	}

	// update the active objects (and kill zombies)
	sysHeadHancho.RManager.updateActiveObjects();

	// check if any actions need to be run and run if necessary
	checkActions();
}

// create the player object
void Logic::createPlayer()
{
	// just add an object with default values? let's seeee---------------------------
	Object test;
	test.setPosition(10, 10);
	test.setSize(20, 20);
	test.setSpriteID(1);
	sysHeadHancho.RManager.addObject(test);
}

// get trigger for a specified action
// -1 if invalid trigger
int Logic::getTrigger(int triggerToGet)
{
	// make sure that input is for a valid action
	if (triggerToGet < 0 || triggerToGet >= Action::TOTAL)
	{
		return -1;
	}

	return triggers[triggerToGet];
}
// checks which actions needs to be run and runs them
void Logic::checkActions()
{
	// check all the actions
	for (int x = 0; x < Action::TOTAL; ++x)
	{
		// get the input system to get the states of the action keys
		Input* inputPtr = (Input*)sysHeadHancho.sysList[sysNames::INPUT];

		// get key state for action
		int curKeyState = inputPtr->getState(x);

		// check if key state matches trigger state
		// run action if it matches
		if (curKeyState == getTrigger(x))
		{
			runAction(x);
		}

		// don't do anything if action should not be run
	}
}

// run actions that have met their trigger
void Logic::runAction(int actionToRun)
{
	// run the action
	switch (actionToRun)
	{
		case Action::LEFT:
			std::cout << "Go left!" << std::endl;
			break;

		case Action::RIGHT:
			std::cout << "Go right!" << std::endl;
			break;

		case Action::UP:
			std::cout << "Go up!" << std::endl;
			break;

		case Action::DOWN:
			std::cout << "Go down!" << std::endl;
			break;

		case Action::ACCEPT:
			std::cout << "Accept!" << std::endl;
			break;

		case Action::ESCAPE:
			sysHeadHancho.exit();
			break;
	}
}
