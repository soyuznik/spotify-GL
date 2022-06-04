#pragma once
#include "Button.h"


class __Pause {
public:
	bool play_texture;
	Button* b;
	__Pause(Shader* shader, WINDOW* windowobj, double posx, double posy, double scale);
};

