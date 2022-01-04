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

class Text {
public:
    unsigned int shaderID;
    std::map<GLchar, Character> Characters;
    Shader* defshader;
    unsigned int VAO, VBO;
    void load_text(WINDOW, std::string font_name);
    void drawText(std::string text, float x, float y, float scale, glm::vec3 color);
    Text(WINDOW window ,std::string path);


};
