#include "Input.h"


// constructor
Input::Input()
{
}

// run/update the input system
void Input::run()
{
	// mostly from old stuff cause simple and it's TEMPPPPPP----------------------------------------------
	if (glfwGetKey(sysHeadHancho.mainWindow.windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		sysHeadHancho.exit();
		//glfwSetWindowShouldClose(sysHeadHancho.mainWindow.windowPtr, GL_TRUE);
	}
}

// deconstructor
Input::~Input()
{
}
