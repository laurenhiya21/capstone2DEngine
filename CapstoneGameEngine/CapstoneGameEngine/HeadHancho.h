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
	public:
		Window mainWindow;
		ResourceManager RManager;
		System* sysList[sysNames::TOTAL];  // all the systems head hancho controls

		// start the engine's systems
		HeadHancho();

		// continue running the engine's systems
		void run();

		// end the engine's systems
		~HeadHancho();
};

extern HeadHancho sysHeadHancho; // global HeadHancho for engine