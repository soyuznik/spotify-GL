#include "Pause.h"
__Pause::__Pause(Shader* shader, WINDOW* windowobj, double posx, double posy, double scale) {
	b = new Button(shader, windowobj, posx, posy, scale);
}