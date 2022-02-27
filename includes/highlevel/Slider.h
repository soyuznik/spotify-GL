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
Slider class
intended to provide a higher level of abstraction
and a dynamic value selector that syncs with audio

----> Inherits Panel (not quite)
*/
class Slider
{
public:
	//for time management near slider
	double crtsongtime = 0.0;
	double fullsongtime = 0.0;
	Shader* shader; // shader that renders slider
	WINDOW* windowobj; // window on which renders
	//font
	Text* txcounter;
	unsigned int ID; // texture ID
	// screen coords
	double posx;
	double posy;
	double scale;

	// value that changes SLIDER DOT
	bool setpos_called = false;

	// Dot screen coords
	double dposx;
	double dposy;
	double dscale;
	// dot texture
	TEXTURE dotTexture = TEXTURE("textures/dot.png");

	// returns audio sample length
	double return_pos(double song_lenght);
	void set_pos(double seconds, double song_lenght); // sets dot position based on audio sample lenght
	Slider(Shader* shader, WINDOW* windowobj, const char* path, double posx, double posy, double scale); // slider constructor
	// creates panel using class variables defined in constructor
	void create_panel(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO,
		double posx, double posy, double scale);
	// changed the panel position on screen
	void change_position(double x, double y);
	//creating a vertex array object with data from "vertices/square.buf"
	VertexArrayObject VAO = VertexArrayObject("vertices/square_super_wide.buf");
	// creates a rectangle shaped - dot
	VertexArrayObject DOT = VertexArrayObject("vertices/square.buf");
	// not usable ----------------------------------------
	void setText(Text* font, std::string text, float scale, float R = 0.0f, float G = 0.0f, float B = 0.0f);
	// accepts input from user
	bool accept_input(glm::vec4 point);
	// create_panel invoker
	void render();

private:
	double setdotpos = 1;
	glm::mat4 model;
};
