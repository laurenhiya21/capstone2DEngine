#pragma once
#include "HeadHancho.h"

// actions that can be done in the game
// each corrospond with an input (keyboard, controller, mouse)
// which is controlled in the Input class
namespace Action
{ 
	enum
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		ACCEPT,
		ESCAPE,
		TOTAL
	};
}


// deals with the updating of objects (including AI)
class Logic: public System
{
	private:
		int triggers[Action::TOTAL]; // the triggers accociated with each action

	public:

		// run/update the logic system
		void run();

		// get trigger for a specified action
		int getTrigger(int triggerToGet);

		// checks which actions needs to be run and runs them
		void checkActions();

		// run action that have met their trigger
		void runAction(int actionToRun);
};
