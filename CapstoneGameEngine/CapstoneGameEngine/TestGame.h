#pragma once
#include <string>
#include "Object.h"
#include "Update.h" // update types
#include "Level.h"

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

// Update behaviour on level1 given the type of update
// update type can be on creation, run time, or on deletion
void level1Update(Object*, Update::Type);

// Update behaviour on level2 given the type of update
// update type can be on creation, run time, or on deletion
void level2Update(Object*, Update::Type);

/*
------------------------------------------------------------------------
	Space Invaders Realated Functions
------------------------------------------------------------------------
*/

// Collision behaviour between the object that transitions to the space invader level 
	// and an another object
void toSpaceInvadersCollision(Object*, Object*);

// Update behaviour on space invaders level given the type of update
// update type can be on creation, run time, or on deletion
void levelSpaceInvadersUpdate(Object*, Update::Type);

// Creates the carrot ship with default starting position
// Takes in the level to create it on
void createCarrot(Level*);

// Creates a bullet (set to inactive and not visable right now)
// Takes in level to create it on and the type of bullet it is
// Type can be "PlayerBullet" or "EnemyBullet"
// returns ptr to new bullet
Object* createBullet(Level*, ObjectType::Type);

// Update behaviour on carrot ship given the type of update
// update type can be on creation, run time, or on deletion
void carrotUpdate(Object*, Update::Type);