#pragma once
#include <string>
#include "Object.h"
#include "Update.h" // update types

// Collision behaviour between an otter an another object
// assumption that obj1 is an otter
void otterCollision(Object* otter, Object* obj2);

// Update behaviour on an otter given the type of update
// update type can be on creation, run time, or on deletion
void otterUpdate(Object* otter, Update::Type t);

// Collision behaviour between an player an another object
// assumption that obj1 is a player
void playerCollision(Object* player, Object* obj2);

// Update behaviour on a player given the type of update
// update type can be on creation, run time, or on deletion
void playerUpdate(Object* player, Update::Type t);

class PlayerData : public ObjectData
{
	public:
		int hp;

};

// Update behaviour on text given the type of update
// update type can be on creation, run time, or on deletion
void textUpdate(Object* text, Update::Type t);