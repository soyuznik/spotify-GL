#pragma once
//WINDOW header that  we use to  create window / add utility
#include "WINDOW.h"
//SHADER header that we use to draw on the screen and  start a shader program
#include "SHADER.h"
//VAO header that we use to store data that is sent to GPU and other utility
#include "VAO.h"
//TEXTURE header that we use to add textures to primitives.
#include "TEXTURE.h"
//TEXT header that  we use to render text
#include "TEXT.h"
//defining a macro for easier drawing and understanding
#define DRAW(n) glDrawArrays(GL_TRIANGLES, 0, n);
class Button
{
public:
	int frames__ = 0;
	Shader* shader;
	WINDOW* windowobj;
	VertexArrayObject* VAO;
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
	//creating a vertex array object with data from "vertices/square.buf"
	
	// loading a texture & font 
	TEXTURE texture = TEXTURE("textures/button.jpg");
	void render();
};

