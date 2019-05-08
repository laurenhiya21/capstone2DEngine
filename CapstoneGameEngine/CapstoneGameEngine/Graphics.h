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
		unsigned vArrayID; // ID of OpenGL vertix array object (a simple square that sprites are based off of)

		void initRenderData(); // initialize the rendering data that openGL uses

	public:
		// constructor
		Graphics();

		// run/update the graphics system
		void run();

		// draw a sprite on the screen with texture
		void drawSprite(Object& obj);

		// deconstructor
		~Graphics();
};