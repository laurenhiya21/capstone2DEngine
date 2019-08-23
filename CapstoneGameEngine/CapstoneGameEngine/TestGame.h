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

// Update behaviour on space invaders start screen level given the type of update
// update type can be on creation, run time, or on deletion
void levelSpaceStartUpdate(Object*, Update::Type);

// Update behaviour on start text given the type of update
// update type can be on creation, run time, or on deletion
void infoTextUpdate(Object*, Update::Type);

// Update behaviour on control text given the type of update
// update type can be on creation, run time, or on deletion
void controlTextUpdate(Object*, Update::Type);

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
		unsigned moveInterval; // how often enemies should move (secs)
		time_t timeSinceLastMove; // time (secs) that enemies have moved last
		bool enemiesMoveRight; // whether enemies are moving right (true) or left (false)
		unsigned enemyVelocity; // how much all enemies main move

		bool runGame; // if game should be playing or not (enemies moving etc)
		bool wonGame; // if game has been won or not (false if either lost or in progress)

		unsigned startLives; // how many lives player starts with in a new game
		unsigned curLives; // how mant lives player currently has
};

// The four edges in the group of enemies
namespace EnemyEdge
{
	enum Edge
	{
		TOP,
		RIGHT,
		BOTTOM,
		LEFT
	};
}

// Creates the carrot ship with default starting position
// Takes in the level to create it on
void createCarrot(Level*);

// Update behaviour on carrot ship given the type of update
// update type can be on creation, run time, or on deletion
void carrotUpdate(Object*, Update::Type);

// Collision behaviour between an carrot an another object
// assumption that obj1 is the carrot
void carrotCollision(Object*, Object*);

// Creates all enemies in a level
// Takes in level to create them in
void createAllEnemies(Level*);

// Creates an enemy
// Takes in level to create it on and position it should spawn in
void createEnemy(Level*, unsigned, unsigned);

// get the nth enemy on given level, where n is a number between 1 and totalNum of enemies
// returns ptr to the chosen enemy
Object* getNthEnemy(Level*, unsigned);

// get the enemy that is on the outer edge of the group of enemies in the given level
// Returns the enemy on the outermost edge
// Edge can be TOP, RIGHT, BOTTOM, or LEFT
// Returns nullptr if no enemies
Object* getEdgeEnemy(Level*, EnemyEdge::Edge);

// checks which direction enemies should move in (based on enemiesMoveRight)
// changes direction to keep enemies within the window
// calls moveAllEnemies based on what direction they should move in
void moveEnemiesCheck(Level*);

// Move all the enemies in the level by the enemyVelocity (one step per call)
// EnemyEdge is uesd as a direction to move enemies
// does not check for bounds and is assumed that given movement is valid
void moveAllEnemies(Level*, EnemyEdge::Edge);

// Update behaviour on a enemy given the type of update
// update type can be on creation, run time, or on deletion
void enemyUpdate(Object*, Update::Type);

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

// Update behaviour on restart text given the type of update
// update type can be on creation, run time, or on deletion
void restartTextUpdate(Object*, Update::Type);

// Update behaviour on lives text given the type of update
// update type can be on creation, run time, or on deletion
void livesTextUpdate(Object*, Update::Type);