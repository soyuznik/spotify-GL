#pragma once
#include <iostream>
#include <map>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SHADER.h"
#include "WINDOW.h"

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};


///Text(WINDOW window, std::string path);
class Text {
public:
	unsigned int shaderID; // text shader
	std::map<GLchar, Character> Characters; // map with all 128 carachters
	Shader* defshader; // text shader
	unsigned int VAO, VBO; // VAO for the text , VBO with square vertices , we use textures on squares to create text
	void load_text(WINDOW, std::string font_name); // loads text from a .tff file
	void drawText(std::string text, float x, float y, float scale, glm::vec3 color); // draws the text , no DRAW(N) neccesray
	Text(WINDOW window, std::string path); // constructor which calls load_text
};
