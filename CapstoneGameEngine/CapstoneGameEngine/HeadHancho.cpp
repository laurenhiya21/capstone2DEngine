#include "HeadHancho.h"
#include "WindowsInterface.h"

#include <iostream> //temp-------------------------------

// start the engine's various managers and necessary parts
void HeadHancho::start()
{
	std::cout << "start engine!" << std::endl;

	// create and start the WindowsInterface system
	WindowsInterface sysWindowsInterface();
}

// continue running the engine
void HeadHancho::run()
{
	std::cout << "run engine!!" << std::endl;
}

// clean up the managers as get ready to end the engine
void HeadHancho::end()
{
	std::cout << "end engine!" << std::endl;

	// end the WindowsInterface system
}