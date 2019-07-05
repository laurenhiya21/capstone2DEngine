#include "TestGame.h"
#include <iostream>

void otterCollision(Object* obj1, Object* obj2)
{
	std::cout << "Collision between Obj ID " << obj1->getID() << " and Obj ID " << obj2->getID() << std::endl;
}
