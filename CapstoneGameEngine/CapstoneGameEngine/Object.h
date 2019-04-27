#pragma once

// default settings
//const bool DEFAULT_ZOMBIE = false;
//const bool DEFAULT_VISABLE = false;

class Object
{
	protected:
		static unsigned freeID; // first free ID

	private:
		unsigned ID; // unique ID for object
		bool zombie; // is object to be deleted?
		bool visable; // is object visable?
		bool active; // does object need to be updated?
		// bounding box?
		// image?
		// w & h?
		
	public:

		// default constructor
		Object();

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