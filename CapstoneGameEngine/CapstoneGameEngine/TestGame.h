#pragma once
#include <string>
#include <cstring> // enemy firing time
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

// Data associated with the space invader level
class SpaceInvaderLevelData : public ObjectData
{
	public: 
		unsigned totalEnemies; // total num enemies cur in the level
		unsigned fireInterval; // time (sec) when enemies should fire
		time_t timeSinceLastFire; // time (secs) that any enemy fired last
		unsigned moveInterval; // how often enemies should move (secs but later want ms)
		time_t timeSinceLastMove; // time (secs) that enemies have moved last------------------------------ change to ms later
		bool enemiesMoveRight; // whether enemies are moving right (true) or left (false)
		unsigned enemyVelocity; // how much all enemies main move
};

// Creates the carrot ship with default starting position
// Takes in the level to create it on
void createCarrot(Level*);

// Update behaviour on carrot ship given the type of update
// update type can be on creation, run time, or on deletion
void carrotUpdate(Object*, Update::Type);

// Creates all enemies in a level
// Takes in level to create them in
void createAllEnemies(Level*);

// Creates an enemy
// Takes in level to create it on and position it should spawn in
//--------------------------------
// might expand this to do whole level of enemies with another function but for now just one at a default position
//--------------------------------
void createEnemy(Level*, unsigned, unsigned);

// get the nth enemy on given level, where n is a number between 1 and totalNum of enemies
// returns ptr to the chosen enemy
Object* getNthEnemy(Level*, unsigned);

// Move all the enemies in the level by the enemyVelocity (one step per call)
// Moves enemies back and forth across screen while slowly advancing forward
// keeps enemies within bounds of level
void moveAllEnemies(Level*);

// Collision behaviour between an enemy an another object
// assumption that obj1 is an enemy
void enemyCollision(Object*, Object*);

// Creates a bullet (set to inactive and not visable right now)
// Takes in level to create it on and the type of bullet it is
// Type can be "PlayerBullet" or "EnemyBullet"
// returns ptr to new bullet
Object* createBullet(Level*, ObjectType::Type);

// Update behaviour on a bullet given the type of update
// update type can be on creation, run time, or on deletion
// can handle both enemy and player bullets
void bulletUpdate(Object*, Update::Type);

// Collision behaviour between bullet and another object
// assumption that obj1 is a bullet
// handles both enemy and player bullets
void bulletCollision(Object*, Object*);

// Update behaviour on score given the type of update
// update type can be on creation, run time, or on deletion
void scoreUpdate(Object*, Update::Type);