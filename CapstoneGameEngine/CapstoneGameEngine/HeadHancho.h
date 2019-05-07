#pragma once

#include "Window.h"
#include "System.h"
#include "ResourceManager.h"

// list of systems that HeadHancho controls
namespace sysNames
{
	enum
	{
		INPUT,
		LOGIC,
		GRAPHICS,
		TOTAL
	};

};

// Manager that takes care of communication between the systems
// Also takes care of starting and ending the systems
class HeadHancho: public System
{
	private:
		bool runGame; // signals if game should stop or continue running

	public:
		Window mainWindow;
		ResourceManager RManager;
		System* sysList[sysNames::TOTAL];  // all the systems head hancho controls

		// start the engine's systems
		HeadHancho();

		// continue running the engine's systems
		void run();

		// mark the game as ready to exit (right no no real checks...)
		void exit();

		// end the engine's systems
		~HeadHancho();
};

extern HeadHancho sysHeadHancho; // global HeadHancho for engine