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

		// setters
		void setZombie(bool);
		void setVisable(bool);

		// deconstructor
		~Object();

};

// set first free id
unsigned Object::freeID = 0;
