#pragma once
//WINDOW header that  we use to  create window / add utility
#include "lowlevel/WINDOW.h"
//SHADER header that we use to draw on the screen and  start a shader program
#include "lowlevel/SHADER.h"
//VAO header that we use to store data that is sent to GPU and other utility
#include "lowlevel/VAO.h"
//TEXTURE header that we use to add textures to primitives.
#include "lowlevel/TEXTURE.h"
//TEXT header that  we use to render text
#include "lowlevel/TEXT.h"
//defining a macro for easier drawing and understanding
#define DRAW(n) glDrawArrays(GL_TRIANGLES, 0, n);
class Button
{
public:
	int frames__ = 0;
	Shader* shader;
	WINDOW* windowobj;
	VertexArrayObject* VAO;
	// loading a texture & font
	TEXTURE* texture = new TEXTURE("textures/button.jpg");
	double posx;
	double posy;
	double scale = 0;
	int* frames;
	int slot;
	Button(Shader* shader, WINDOW* windowobj, double posx, double posy, double scale, int slot, std::string PATH = "vertices/square.buf");
	void create_button(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO, TEXTURE* texture,
		double posx, double posy, double scale, int* slot);
	void setText(Text* font, std::string text, float scale, float R = 0.0f, float G = 0.0f, float B = 0.0f);
	void change_position(double x, double y);
	void set_texture(std::string PATH);
	//creating a vertex array object with data from "vertices/square.buf"

	

	void render();
	void accept_input(glm::vec4 point, int slot);
private:
	glm::mat4 modl = glm::mat4(1.0f);
};
