#pragma once

// default settings
//const bool DEFAULT_ZOMBIE = false;
//const bool DEFAULT_VISABLE = false;

#include <glm/glm.hpp> // vectors/matricies

class Object
{
	protected:
		static unsigned freeID; // first free ID

	private:
		unsigned ID; // unique ID for object
		bool zombie; // is object to be deleted?
		bool visable; // is object visable?
		bool active; // does object need to be updated?
		glm::vec2 position; // where object is on screen
		glm::vec2 size; // size of object (w x h)
		glm::vec3 colour; // colour of object
		float rotation; // rotation of object (0.0f if none)
		// texture
		
	public:

		// default constructor
		Object(bool z = false, bool v = true, bool a = true, glm::vec2 pos = glm::vec2(0,0), glm::vec2 s = glm::vec2(1, 1), glm::vec3 c = glm::vec3(1.0f), float r = 0.0f);

		// getters
		bool getZombie();
		bool getVisable();
		unsigned getID();
		bool getActive();

		// setters
		void setZombie(bool);
		void setVisable(bool);
		void setActive(bool);

		// deconstructor
		~Object();

};