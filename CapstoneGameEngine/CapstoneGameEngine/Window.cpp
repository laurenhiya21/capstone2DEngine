#include "Window.h"
#include <iostream> //cin & cout
#include "HeadHancho.h"
#include "Graphics.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// default constructor
Window::Window(unsigned w, unsigned h)
{
	screenWidth = w;
	screenHeight = h;
}

int Window::makeWindow()
{
	// glfw window creation
	// --------------------
	windowPtr = glfwCreateWindow(screenWidth, screenHeight, "Capstone Game Engine", NULL, NULL);
	if (windowPtr == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(windowPtr);
	glfwSetFramebufferSizeCallback(windowPtr, framebuffer_size_callback);

	return 0;
}

// gettors-----------------------------------------------------------------------------------------

unsigned Window::getWidth()
{
	return screenWidth;
}

unsigned Window::getHeight()
{
	return screenHeight;
}

// deconstructor
Window::~Window()
{

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}