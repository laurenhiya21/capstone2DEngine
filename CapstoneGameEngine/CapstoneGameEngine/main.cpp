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

	// create test objects
	ResourceManager RManager;
	Object o1;
	Object o2;
	Object o3;
	Object o4;

	// add objects to manager
	RManager.addObject(o1);
	RManager.addObject(o2);
	RManager.addObject(o3);
	RManager.addObject(o4);

	// get num object before deltion
	unsigned before = RManager.getNumObjects();

	// remove an object
	RManager.removeObject(o3.getID());

	// get num object after deltion
	unsigned after = RManager.getNumObjects();

	// find an object
	int o4Spot = RManager.findObject(o4.getID());

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