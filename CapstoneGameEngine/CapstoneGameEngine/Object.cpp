#include "Object.h"

// set first free id
unsigned Object::freeID = 0;

// default constructor
Object::Object()
{
	// set the id and set the next free id
	ID = freeID;
	++freeID;

	//set zombie, visable, and active
	zombie = false;
	visable = true;
	active = true;
}

//----------------------------------------------------------------------------------
// Getters------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------

bool Object::getZombie()
{
	return zombie;
}

bool Object::getVisable()
{
	return visable;
}

unsigned Object::getID()
{
	return ID;
}

bool Object::getActive()
{
	return active;
}

//----------------------------------------------------------------------------------
// Setters------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------

void Object::setZombie(bool z)
{
	zombie = z;
}

void Object::setVisable(bool v)
{
	visable = v;
}

void Object::setActive(bool a)
{
	active = a;
}

// deconstructor
Object::~Object()
{
}
