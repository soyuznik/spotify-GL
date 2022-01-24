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

class ClickEventCanceller
{
public:
	Shader* shader;
	WINDOW* windowobj;
	unsigned int ID;
	double posx;
	double posy;
	double scale;

	ClickEventCanceller(Shader* shader, WINDOW* windowobj, const char* path, double posx, double posy, double scale);
	void create_canceller(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO,
		double posx, double posy, double scale);
	void change_position(double x, double y);
	//creating a vertex array object with data from "vertices/square.buf"
	VertexArrayObject VAO = VertexArrayObject("vertices/square_higher_wider.buf");
	


	void render();
};

