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
class Slider
{
public:
	Shader* shader;
	WINDOW* windowobj;
	unsigned int ID;
	double posx;
	double posy;
	double scale;

	
	bool setpos_called = false;
	double dposx;
	double dposy;
	double dscale;



	double return_pos(double song_lenght);
	void set_pos(double seconds, double song_lenght);
	Slider(Shader* shader, WINDOW* windowobj, const char* path, double posx, double posy, double scale);
	void create_panel(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO,
		double posx, double posy, double scale);
	void change_position(double x, double y);
	//creating a vertex array object with data from "vertices/square.buf"
	VertexArrayObject VAO = VertexArrayObject("vertices/square_super_wide.buf");
	VertexArrayObject DOT = VertexArrayObject("vertices/square.buf");
	void setText(Text* font, std::string text, float scale, float R = 0.0f, float G = 0.0f, float B = 0.0f);
	bool accept_input(glm::vec4 point);
	void render();

private:
	double setdotpos = 1;
	glm::mat4 model;
};
