#pragma once

// a system that communicates with the Windows related functions
// needed to get a window to run the game/engine
class WindowsInterface
{
	public:

		// start the WindowsInterface system
		void start();

		// continue running the WindowsINterface system
		void run();

		// end the Windows Interface system
		void end();
};
