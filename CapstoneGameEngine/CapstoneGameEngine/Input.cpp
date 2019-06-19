#include "Input.h"
#include <iostream> //TEMP OUTPUT

// constructor
Input::Input()
{
}

// run/update the input system
void Input::run()
{
	//std::cout << "Space" << glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_SPACE) << std::endl;

	// mostly from old stuff cause simple and it's TEMPPPPPP----------------------------------------------
	if (glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		sysHeadHancho.exit();
		//glfwSetWindowShouldClose(sysHeadHancho.mainWindow.windowPtr, GL_TRUE);
	}

	if (glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_W) == GLFW_PRESS)
	{
		std::cout << "W Pressed!" << std::endl;
	}

	if (glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_S) == GLFW_PRESS)
	{
		std::cout << "S Pressed!" << std::endl;
	}

	if (glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_A) == GLFW_PRESS)
	{
		std::cout << "A Pressed!" << std::endl;
	}

	if (glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_D) == GLFW_PRESS)
	{
		std::cout << "D Pressed!" << std::endl;
	}
}

// deconstructor
Input::~Input()
{
}
