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

//* Checkbox(Shader* _shader, WINDOW* _windowobj, double _posx, double _posy, double _scale, std::string PATH = "Resources/vertices/square.buf");
class Checkbox{
	
public:
	TEXTURE* _t_unactive;
	TEXTURE* _t_active;
	bool is_active();
	void set_activebool(bool __active);
	void indent(std::string ident);
	Checkbox(Shader* _shader, WINDOW* _windowobj, double _posx, double _posy, double _scale,  std::string PATH = "Resources/vertices/square.buf");
	float last = 0;
	void set_active(std::string active_path);
	void set_unactive(std::string unactive_path);
	int frames__ = 0;
	//saving objects
	Shader* shader;
	WINDOW* windowobj;
	VertexArrayObject* VAO;
	// loading a texture & font
	TEXTURE* texture;
	double posx;
	double posy;
	double scale = 0;
	int* frames;
	//small data sample
	std::string obj_ident = "not defined";
	//button constructor
	
	// called inside render()
	void create_button(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO, TEXTURE* texture,
		double posx, double posy, double scale);
	//sets button text
	void setTextM(Text* font, std::string text, float scale, float R, float G, float B);
	void setText(Text* font, std::string text, float scale, float R = 0.0f, float G = 0.0f, float B = 0.0f);
	//changes button position based on screen
	void change_position(double x, double y);
	//set custom texture.
	void set_texture(std::string PATH);

	//check for clicks
	bool is_clicked();
	//render the button on screen based on class arguments
	void render();
	// check if point inside 2 triangles
	void accept_input(glm::vec4 point);
private:
	bool active = false;
	//if clicked = true
	bool clicked = false;
	//for changing color to grayer if clicked
	bool change_color = false;
	// matrix for position on screen (screen coords)
	glm::mat4 modl = glm::mat4(1.0f);
};