#include "Graphics.h"
#include "Windowx.h"
#include "HeadHancho.h"
#include "Shader.h"

// itilize graphics things
Graphics::Graphics()
{
	// Load sprite shader
	sysHeadHancho.RManager.LoadShader("../shaders/sprite.vs", "../shaders/sprite.frag", "sprite");

	// Configure shaders
	// creates projection matrix to scale, rotate, translate objects
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(sysHeadHancho.mainWindow.getWidth()), static_cast<GLfloat>(sysHeadHancho.mainWindow.getHeight()), 0.0f, -1.0f, 1.0f); //-----------not sure which include?

	// ---------------------------?????------------------------------------
	sysHeadHancho.RManager.getShader("sprite").use().setInteger("image", 0);
	sysHeadHancho.RManager.getShader("sprite").setMatrix4("projection", projection);
}

// draw a sprite on the screen (add texture later)
void Graphics::drawSprite(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
	// get the sprite shader & set to use
	Shader sShader = sysHeadHancho.RManager.getShader("sprite");
	sShader.use();

	// set up a matrix to be used for transformation (start as identidy)
	glm::mat4 model(1.0);

	// transform the sprite appropriatly
	// translate -> rotate -> scale
	model = glm::translate(model, glm::vec3(position, 0.0f)); // translate

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // scale sprite

	//--------------------?? not super sure-----------------------------------------------------------
	sShader.setMatrix4("model", model);

	// some more stuff in spriterenderer::draw sprite but don't know atm

}

// deconstructor
Graphics::~Graphics()
{

}

//TEMPPppppppppppppppppppppppppp

// renders the screen
int render()
{
	// render loop
	// -----------
	while (!glfwWindowShouldClose(sysHeadHancho.mainWindow.windowPtr))
	{
		// input
		// -----
		processInput(sysHeadHancho.mainWindow.windowPtr);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render all the visable objects
		sysHeadHancho.RManager.renderVisable();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(sysHeadHancho.mainWindow.windowPtr);
		glfwPollEvents();
	}

	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}