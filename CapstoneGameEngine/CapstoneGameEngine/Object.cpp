#include "Object.h"

// set first free id
unsigned Object::freeID = 0;

// default constructor (default parameters for each)
Object::Object(bool z, bool v, bool a, glm::vec2 pos, glm::vec2 s, glm::vec3 c, float r)
{
	// set the id and set the next free id
	ID = freeID;
	++freeID;

	//set all of the other parameters
	zombie = z;
	visable = v;
	active = a;
	position = pos;
	size = s;
	colour = c;
	rotation = r;
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

glm::vec2 Object::getPosition()
{
	return position;
}

glm::vec2 Object::getSize()
{
	return size;
}

glm::vec3 Object::getColour()
{
	return colour;
}

float Object::getRotation()
{
	return rotation;
}

Texture& Object::getSprite()
{
	return sprite;
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

void Object::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Object::setSize(float x, float y)
{
	size.x = x;
	size.y = y;
}

void Object::setRotation(float r)
{
	rotation = r;
}

// deconstructor
Object::~Object()
{
}
