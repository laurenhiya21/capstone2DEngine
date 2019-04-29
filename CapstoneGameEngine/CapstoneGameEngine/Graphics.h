#pragma once
#include <glad.h>  //-----------
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"
#include "HeadHancho.h"

//SET UP GLM TO ACTIALL BE FOUND YO

int render(); // renders the screen
void processInput(GLFWwindow *window);

class Graphics
{
	// constructor
	Graphics();

	// deconstructor
	~Graphics();
};