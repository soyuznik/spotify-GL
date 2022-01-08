#pragma once
//WINDOW header that  we use to  create window / add utility
#include "WINDOW.h"
//SHADER header that we use to draw on the screen and  start a shader program
#include "SHADER.h"
//VAO header that we use to store data that is sent to GPU and other utility
#include "VAO.h"
//TEXTURE header that we use to add textures to primitives.
#include "TEXTURE.h"

//defining a macro for easier drawing and understanding
#define DRAW(n) glDrawArrays(GL_TRIANGLES, 0, n);
class Button
{
public:
	Shader* shader;
	WINDOW* windowobj;
	double posx;
	double posy; 
	double scale;
	int* frames;
	int* slot;
	Button(Shader* shader, WINDOW* windowobj, double posx, double posy, double scale, int* frames, int* slot);
	void create_button(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO, TEXTURE* texture,
		double posx, double posy, double scale, int* frames, int* slot);
	//creating a vertex array object with data from "vertices/square.buf"
	VertexArrayObject VAO = VertexArrayObject("vertices/square.buf");
	// loading a texture & font 
	TEXTURE texture = TEXTURE("textures/button.jpg");
	void render();
};

