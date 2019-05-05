/* 2D Game Engine!
	Lauren Bratt
*/

#include <iostream> //cin & cout
#include "HeadHancho.h"
#include "Windowx.h"
#include "Graphics.h"
#include "ResourceManager.h"

//---------MOVE LATER YO0000000000000000000--------------------------------

void processInput(GLFWwindow *window);

//-------END OF MOVE LATER YOOO--------------------------------------------

HeadHancho sysHeadHancho; // global HeadHancho for engine

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