#pragma once

// Manager that takes care of communication between the systems
// Also takes care of starting and ending the systems
class HeadHancho
{
	public:

		// start the engine's systems
		void start();

		// continue running the engine's systems
		void run();

		// end the engine's systems
		void end();

};