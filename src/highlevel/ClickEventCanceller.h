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
/*

ClickEventCanceller class .
intended to block click events so ListObject items dont get triggered
when they are not seen on screen directly
*/
class ClickEventCanceller
{
public:
	Shader* shader; // shader which renders it
	WINDOW* windowobj; // which window
	unsigned int ID;
	//screen pos and scale
	double posx;
	double posy;
	double scale;
	//constructor
	ClickEventCanceller(Shader* shader, WINDOW* windowobj, const char* path, double posx, double posy, double scale);
	void create_canceller(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO,
		double posx, double posy, double scale);
	void change_position(double x, double y);
	//creating a vertex array object with data from "vertices/square.buf"
	VertexArrayObject VAO = VertexArrayObject("Resources/vertices/square_higher_wider.buf");

	//checks if the point should be blocked
	bool should_block(glm::vec4 point);
	void render();
private:
	glm::mat4 model;
};
