/* 2D Game Engine!
	Lauren Bratt
*/

#include <iostream> //cin & cout
#include "HeadHancho.h"
#include "Window.h"
#include "Graphics.h"
#include "ResourceManager.h"

HeadHancho sysHeadHancho; // global HeadHancho for engine

//---------MOVE LATER YO0000000000000000000-------------------------------
#include <glad.h>  //-----------
#include <glfw3.h> //------------

void processInput(GLFWwindow *window);

//-------END OF MOVE LATER YOOO--------------------------------------------

int main()
{
	//std::cout << "Test!" << std::endl;

	//sysHeadHancho.start();
	//sysHeadHancho.run();
	//sysHeadHancho.end();

	Window newWindow;
	newWindow.makeWindow();

	//makeWindow();
	render();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	return 0;
}


//MOVE LAYER YOOO----------------------------------------------------