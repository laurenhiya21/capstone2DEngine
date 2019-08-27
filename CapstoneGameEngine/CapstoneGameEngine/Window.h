#pragma once

// settings
const unsigned int DEFAULT_SCR_WIDTH = 800;
const unsigned int DEFAULT_SCR_HEIGHT = 600;

struct GLFWwindow;

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

		// gettors
		unsigned getWidth();
		unsigned getHeight();

		// deconstructor
		~Window();

		GLFWwindow* windowPtr;
};