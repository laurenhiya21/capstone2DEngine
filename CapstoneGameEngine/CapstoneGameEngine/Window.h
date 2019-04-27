#pragma once
#include <iostream> //cin & cout
#include <glad.h>  //-----------
#include <glfw3.h>

// settings
const unsigned int DEFAULT_SCR_WIDTH = 800;
const unsigned int DEFAULT_SCR_HEIGHT = 600;

// global pointer to created window
extern GLFWwindow* window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Window
{
	private:
		// dimensions of window
		unsigned int screenWidth;
		unsigned int screenHeight;

	public:
		// default constructor
		Window(unsigned w = DEFAULT_SCR_WIDTH, unsigned h = DEFAULT_SCR_HEIGHT);

		int makeWindow();

		// deconstructor
		~Window();
};