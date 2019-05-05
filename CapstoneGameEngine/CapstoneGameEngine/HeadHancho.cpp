#include "HeadHancho.h"

#include <iostream> //temp-------------------------------

#include "Input.h"
#include "Logic.h"
#include "Graphics.h"

// start the engine's various managers and necessary parts
HeadHancho::HeadHancho()
{
	std::cout << "start engine!" << std::endl;

	// create the main window
	mainWindow.makeWindow();

	// add the different systems to headHancho's list
	sysList[sysNames::INPUT] = new Input();
	sysList[sysNames::LOGIC] = new Logic();
	sysList[sysNames::GRAPHICS] = new Graphics();
}

// continue running the engine
void HeadHancho::run()
{
	std::cout << "run engine!!" << std::endl;

	// the main rendering loop
	while (true)
	{
		// run/update headHancho's systems
		for (int x = 0; x < sysNames::TOTAL; ++x)
		{
			sysList[x]->run();
		}

		// need more conditions here!------------------------------------
		break;
	}
}

// clean up the managers as get ready to end the engine
HeadHancho::~HeadHancho()
{
	std::cout << "end engine!" << std::endl;

	// remove headHancho's systems
	for (int x = 0; x < sysNames::TOTAL; ++x)
	{
		delete sysList[x];
		sysList[x] = nullptr;
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();


	// end the WindowsInterface system
}