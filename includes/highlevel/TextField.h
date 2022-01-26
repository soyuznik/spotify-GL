#pragma once
#include "highlevel/Panel.h"
#include "lowlevel/TEXT.h"
class TextField
{
public:
	Shader* shader;
	WINDOW* window;
	double posx;
	double posy;
	Panel* panel;
	Text* antonio_bold;
	std::string* tlog = new std::string("");
	int logframes = 0;
	int logticks = 0;
	TextField(Shader* shader, WINDOW* window, double posx, double posy);
	void render();
	void logkey();
	std::string text();

};
