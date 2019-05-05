#include "Logic.h"

// run/update the logic system
void Logic::run()
{
	// update the active objects (and kill zombies)
	sysHeadHancho.RManager.updateActiveObjects();
}
