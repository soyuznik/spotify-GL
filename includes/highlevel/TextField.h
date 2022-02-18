#pragma once
#include "highlevel/Panel.h"
#include "lowlevel/TEXT.h"
class TextField
{
public:
	Shader* shader;
	WINDOW* window;
	std::string dots = "";
	std::string save_key = "";
	int repeats = 0;
	bool was_initiated = false;
	int time = 0;
	bool showing = false;
	double posx;
	double posy;
	Panel* panel;
	Text* antonio_bold;
	int logframes = 0;
	int logticks = 0;
	TextField(Shader* shader, WINDOW* window, double posx, double posy);
	void render();
	void logkey();
	void check_input();
	std::string text();
	std::string* tlog = new std::string("");
};
