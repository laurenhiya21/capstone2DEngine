#include "Object.h"

// set first free id
unsigned Object::freeID = 0;

// default constructor
Object::Object()
{
	// set the id and set the next free id
	ID = freeID;
	++freeID;

	//set zombie and visable
	zombie = false;
	visable = true;
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


// deconstructor
Object::~Object()
{
}
