#include "TextRenderer.h"

#include <glm/gtc/matrix_transform.hpp> // mathy tranformation stuff
#include "HeadHancho.h" // get the resource manager to add shaders
#include "CoreObjects.h" //text contents

#include "ft2build.h" // freeType library: for rendering the text on screen
#include FT_FREETYPE_H

// constructor (not sure what w and h should be???)------------------------
TextRenderer::TextRenderer(int width, int height)
{
	// Load sprite shader from the files (and adds it in if it's not already there)
	sysHeadHancho.RManager.LoadShader("../shaders/text.vs", "../shaders/text.frag", "text");

	// configure the shader
	sysHeadHancho.RManager.getShader("text").setMatrix4("projection", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f), true);
	sysHeadHancho.RManager.getShader("text").setInteger("text", 0);

	// Configure VAO/VBO for texture quads-----------------
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// pre-compiles a list of cahracters given a font
void TextRenderer::load(std::string font, unsigned fontSize)
{
	// clear previously loaded characters
	characterList.clear();

	// initilize and loadt the FreeType library
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) // All functions return a value different than 0 whenever an error occurred
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		__debugbreak;
	}

	// Load font as face
	FT_Face face;
	if (FT_New_Face(ft, font.c_str(), 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		__debugbreak;
	}

	// Set size to load glyphs
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Then for the first 128 ASCII characters, pre-load/compile their characters and store them
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
			);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

		characterList.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

// Renders a string of text using the precompiled list of characters
//
void TextRenderer::renderText(Object& textToRender)
{
	// gets the text that needs to be rendered
	TextData* textData = (TextData*)textToRender.getObjectDataPtr();
	float x = textToRender.getPosition().x;

	//std::string text, float x, float y, float scale, glm::vec3 color
	// set up the shader to use
	sysHeadHancho.RManager.getShader("text").use();
	sysHeadHancho.RManager.getShader("text").SetVector3f("textColor", textToRender.getColour());
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = textData->data.begin(); c != textData->data.end(); c++)
	{
		Character ch = characterList[*c];

		float xpos = x + ch.bearing.x * textToRender.getSize().x;
		float ypos = textToRender.getPosition().y + (characterList['H'].bearing.y - ch.bearing.y) * textToRender.getSize().y;

		float w = ch.size.x * textToRender.getSize().x;
		float h = ch.size.y * textToRender.getSize().y;

		// Update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 0.0 },
			{ xpos,     ypos,       0.0, 0.0 },

			{ xpos,     ypos + h,   0.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 1.0 },
			{ xpos + w, ypos,       1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph
		x += (ch.advance >> 6) * textToRender.getSize().x; // Bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}