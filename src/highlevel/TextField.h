#pragma once

// using panel abstraction
#include "highlevel/Panel.h"
// using TEXT class cause its A TEXTFIELD
#include "lowlevel/TEXT.h"

/*
TextField Class
intended to make user text input easier
*/
class TextField
{
public:
	Shader* shader; // shader to render text field box
	WINDOW* window; // on which window
	unsigned int activeID = TEXTURE("Resources/textures/transparent_searchbar_active.png").ID;
	unsigned int unactiveID = TEXTURE("Resources/textures/transparent_searchbar.png").ID;
	// text management Variables
	std::string save_key = "";
	int repeats = 0;
	double __CTIME_LAST = glfwGetTime();
	bool was_initiated = false;
	int time = 0;
	bool SAVE_KEY_HOLDING = false;
	// if it shows the "  | " or not
	bool showing = false;

	// save screen pos
	double posx;
	double posy;

	// 2 structures of which TEXTFIELD made of
	Panel* panel;
	Text* antonio_bold;

	int logframes = 0;
	int logticks = 0;

	//constructor
	TextField(Shader* shader, WINDOW* window, double posx, double posy);
	void render(); // render
	void logkey(); // log user key press
	
	void check_input(); // check if user invoked the TEXTFIELD
	std::string text(); // returns  the text
	std::string* tlog = new std::string(""); // current displayed text
};
