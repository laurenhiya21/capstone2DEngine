#include "Graphics.h"

// itilize graphics things
Graphics::Graphics()
{
	// Load sprite shader
	// need to change how this is called!-----------------------------------------------------
	sysHeadHancho.RManager.LoadShader("../shaders/sprite.vs", "../shaders/sprite.frag", nullptr, "sprite");

	// Configure shaders
	// creates projection matrix to scale, rotate, translate objects
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f); 
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
}

// deconstructor
Graphics::~Graphics()
{

}

// renders the screen
int render()
{
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render all the visable objects
		sysHeadHancho.RManager.renderVisable();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

//TEMPPppppppppppppppppppppppppp

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}