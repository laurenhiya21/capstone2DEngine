#pragma once

//We are statically linking glew, so we have to define GLEW_STATIC
//for the linker to be happy
#define GLEW_STATIC

#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "System.h"
#include "Object.h" // for drawing the objects

class Graphics: public System
{
	private:

	public:
		// constructor
		Graphics();

		// run/update the graphics system
		void run();

		// draw a sprite on the screen (add texture later)
		void drawSprite(Object& obj);

		// deconstructor
		~Graphics();
};