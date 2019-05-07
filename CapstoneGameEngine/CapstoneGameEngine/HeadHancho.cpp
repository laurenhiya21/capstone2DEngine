#include "HeadHancho.h"

#include <iostream> //temp-------------------------------

#include "Input.h"
#include "Logic.h"
#include "Graphics.h"

// start the engine's various managers and necessary parts
HeadHancho::HeadHancho()
{
	std::cout << "start engine!" << std::endl;

	// set the game to continue running by default
	runGame = true;

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
	while (runGame)
	{
		// run/update headHancho's systems
		for (int x = 0; x < sysNames::TOTAL; ++x)
		{
			// check if any events happened (like input)
			glfwPollEvents();

			// run the systems
			sysList[x]->run();
		}

		// might need to do this or somewhere else but not sure----------
		// but it swaps the front and back buffer to minimize flicker
		//glfwSwapBuffers(sysHeadHancho.mainWindow.windowPtr);

		// need more conditions here?------------------------------------
		//break;
	}
}

// mark the game as ready to exit (right no no real checks...)
void HeadHancho::exit()
{
	runGame = false;
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