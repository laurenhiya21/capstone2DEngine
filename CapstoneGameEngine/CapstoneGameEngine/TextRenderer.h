#pragma once
#include <glew.h>
#include <glm/glm.hpp>

#include <map>

// Holds all state information relevant to a character as loaded using FreeType
struct Character 
{
	unsigned textureID;   // ID handle of the glyph texture
	glm::ivec2 size;    // Size of glyph
	glm::ivec2 bearing; // Offset from baseline to left/top of glyph
	unsigned advance;     // Horizontal offset to advance to next glyph
};

// For rendering text on screen
class TextRenderer
{
	private:
		// render state?--------------
		unsigned VAO;
		unsigned VBO;

		// a list of pre-comiled characters
		std::map<char, Character> characterList;

	public:
		// constructor
		TextRenderer(int width, int height);

		// pre-compiles a list of cahracters given a font
		void load(std::string font, unsigned fontSize);

		// Renders a string of text using the precompiled list of characters
		void renderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
};