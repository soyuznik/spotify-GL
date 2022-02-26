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
Panel class
intended for creating a rectangle shaped figure fast.
 and to offer a layer of abstraction
*/
class Panel
{
public:
	Shader* shader; // rendering shader
	WINDOW* windowobj; // window on which to render
	unsigned int ID; // texture ID
	double posx;
	double posy;
	double scale; // screen coords
	// Panel constructor
	Panel(Shader* shader, WINDOW* windowobj, const char* path, double posx,
		double posy, double scale, std::string PATH = "vertices/square_extra_wide.buf");
	// creates panel using class variables
	void create_panel(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO,
		double posx, double posy, double scale);
	// changes coordinates
	void change_position(double x, double y);
	//creating a vertex array object with data from "vertices/square.buf"
	VertexArrayObject* VAO; // custom shape
	// sets text ---- not usable currently
	void setText(Text* font, std::string text, float scale, float R = 0.0f, float G = 0.0f, float B = 0.0f);
	// accepts input --- not usable currently
	bool accept_input(glm::vec4 point);
	// create_panel invoker
	void render();

private:
	glm::mat4 model;
};
