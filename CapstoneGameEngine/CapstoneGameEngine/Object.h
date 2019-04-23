#pragma once

// default settings
const bool DEFAULT_ZOMBIE = false;
const bool DEFAULT_VISABLE = false;

class Object
{
	private:

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

		// setters
		void setZombie(bool);
		void setVisable(bool);

		// deconstructor
		~Object();

};
