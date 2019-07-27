#pragma once

// default settings
//const bool DEFAULT_ZOMBIE = false;
//const bool DEFAULT_VISABLE = false;

#include <glm/glm.hpp> // vectors/matricies
#include "Texture.h" // texture of the object
#include "Update.h" // update types
#include "ObjectData.h" 

class Level; // forward declare level

// Types of Objects that exist
// Used for checking if certain updates should be done
// Or what should be done in collisions
namespace ObjectType
{
	enum Type
	{
		PLAYER,
		OTTER,
		TEXT,
		LEVEL,
		TO_SPACE_INVADERS,
		CARROT,
		PLAYER_BULLET,
		ENEMY_BULLET,
		TOTAL
	};
}

// forward delcare object so collisionFunction can take it as a param
class Object;

// functions that are used to update Objects
// takes in what type of update is being preformed (created, updated, or destroyed)
typedef void(*updateFunction)(Object*, Update::Type);

// functions that are used to determine collision behvavior with other objcest
// takes in a ptr to the object that was collided with
typedef void(*collisionFunction)(Object*, Object*);

class Object
{
	protected:
		static unsigned freeID; // first free ID

	private:
		unsigned ID; // unique ID for object
		std::string name; // name of object (not necessarily unique)
		bool zombie; // is object to be deleted?
		bool visable; // is object visable?
		bool active; // does object need to be updated?
		glm::vec2 position; // where object is on screen
		glm::vec2 size; // size of object (w x h)
		glm::vec3 colour; // colour of object
		float rotation; // rotation of object (0.0f if none)
		unsigned spriteID; // ID of texture/sprite of the object
		ObjectType::Type type; // associated with ObjectType, used for checking object updates and collisions
		updateFunction updatePtr; // the function used to update the object
		collisionFunction collisionPtr; // the function used to figure out collision behaviour with other objects
		ObjectData* objDataPtr; // ptr to Object specfic data (like player stats or text)
		Level* levelPtr; // ptr to the level that the Object is in
		
	public:

		// default constructor
		Object(bool z = false, bool v = true, bool a = true, glm::vec2 pos = glm::vec2(0,0), glm::vec2 s = glm::vec2(1, 1), glm::vec3 c = glm::vec3(1.0f), float r = 0.0f);

		// update position by relative amount (instead of exact coordinate)
		void updatePosition(int x, int y);

		// getters
		std::string getName();
		bool getZombie();
		bool getVisable();
		unsigned getID();
		bool getActive();
		glm::vec2 getPosition();
		glm::vec2 getSize();
		glm::vec3 getColour();
		float getRotation();
		unsigned getSpriteID();
		ObjectType::Type getType();
		collisionFunction getCollisionPtr();
		updateFunction getUpdatePtr();
		ObjectData* getObjectDataPtr();
		Level* getLevelPtr();

		// setters
		void setName(std::string);
		void setZombie(bool);
		void setVisable(bool);
		void setActive(bool);
		void setPosition(float x, float y);
		void setSize(float x, float y);
		void setRotation(float r);
		void setSpriteID(unsigned i);
		void setType(ObjectType::Type);
		void setColour(glm::vec3);
		void setCollisionFunction(collisionFunction newFunct);
		void setUpdateFunction(updateFunction newFunct);
		void setObjectDataPtr(ObjectData* newData);
		void setLevelPtr(Level* newLevel);

		// deconstructor
		~Object();

};