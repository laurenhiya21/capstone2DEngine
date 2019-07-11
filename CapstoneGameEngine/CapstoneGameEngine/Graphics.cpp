#include "Graphics.h"
#include "Window.h"
#include "HeadHancho.h"
#include "Shader.h"

// initialize the rendering data that openGL uses
void Graphics::initRenderData()
{
	// Configure VAO/VBO
	unsigned VBO;
	float vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &vArrayID);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(vArrayID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// itilize graphics things
Graphics::Graphics()
{
	glewExperimental = GL_TRUE; // make sure to allow all aviable glew functionality
	glewInit(); // initilize glew before using

	// Check for any errors from init glew
	glGetError();

	// Load sprite shader from the files (and adds it in if it's not already there)
	sysHeadHancho.RManager.LoadShader("../shaders/sprite.vs", "../shaders/sprite.frag", "sprite");

	// Configure shaders
	// creates projection matrix to scale, rotate, translate objects
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(sysHeadHancho.mainWindow.getWidth()), static_cast<GLfloat>(sysHeadHancho.mainWindow.getHeight()), 0.0f, -1.0f, 1.0f); //-----------not sure which include?

	// ---------------------------?????------------------------------------
	sysHeadHancho.RManager.getShader("sprite").use().setInteger("image", 0);
	sysHeadHancho.RManager.getShader("sprite").setMatrix4("projection", projection);

	// initialize the render data used by openGL
	initRenderData();

	// load all of the used textures
	sysHeadHancho.RManager.loadAllTextures();

	// start up the text renderer
	tRender = new TextRenderer(800,600);

	// load the font(s)
	tRender->load("../fonts/OCRAEXT.TTF", 24);
}

// run/update the graphics system
void Graphics::run()
{
	// render all visable objects
	// glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //not sure if need this?
	glClear(GL_COLOR_BUFFER_BIT); // clear old screen first
	sysHeadHancho.RManager.renderVisable();

	// temp draw test text-------------------------------------------------------------------!!!!!!
	tRender->renderText("test text!", 250.0f, 300.0f, 1.0f);
}

// draw a sprite on the screen (add texture later)
void Graphics::drawSprite(Object& obj)
{
	// get the sprite shader & set to use
	Shader sShader = sysHeadHancho.RManager.getShader("sprite");
	sShader.use();

	// set up a matrix to be used for transformation (start as identidy)
	glm::mat4 model(1.0);

	// transform the sprite appropriatly
	// translate -> rotate -> scale
	model = glm::translate(model, glm::vec3(obj.getPosition(), 0.0f)); // translate

	model = glm::translate(model, glm::vec3(0.5f * obj.getSize().x, 0.5f * obj.getSize().y, 0.0f)); // move origin of rotation to center
	model = glm::rotate(model, obj.getRotation(), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
	model = glm::translate(model, glm::vec3(-0.5f * obj.getSize().x, -0.5f * obj.getSize().y, 0.0f)); // move origin back

	model = glm::scale(model, glm::vec3(obj.getSize(), 1.0f)); // scale sprite

	//--------------------?? not super sure-----------------------------------------------------------
	sShader.setMatrix4("model", model);

	// Render textured quad-------------------------------------------------
	sShader.SetVector3f("spriteColor", obj.getColour());

	// set the active texture to draw it
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj.getSpriteID());

	glBindVertexArray(vArrayID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	// some more stuff in spriterenderer::draw sprite but don't know atm

}

// deconstructor
Graphics::~Graphics()
{
	// clean up the textRenderer
	delete tRender;
}