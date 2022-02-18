#include "TextField.h"
#include "lowlevel/UTILITY.h"

TextField::TextField(Shader* shader_, WINDOW* window_, double posx_, double posy_) {
	shader = shader_;
	window = window_;
	posx = posx_;
	posy = posy_;

	Panel* panel__ = new Panel(shader, window, "textures/button.jpg", posx + 100, posy, 0.15f);
	Text* antonio_bold__ = new Text(*window, "fonts/Antonio-Bold.ttf");
	panel = panel__;
	antonio_bold = antonio_bold__;
}
std::string TextField::text() {
	std::string text__ = *tlog;
	return text__;
}
void TextField::logkey() {
	if (!was_initiated) return;
	std::map<std::string, int> k{
			{ "a", GLFW_KEY_A},//letters
			{ "b" , GLFW_KEY_B },
			{ "c" , GLFW_KEY_C },
			{ "d" , GLFW_KEY_D },
			{ "e" , GLFW_KEY_E },
			{ "f" , GLFW_KEY_F },
			{ "g" , GLFW_KEY_G },
			{ "h" , GLFW_KEY_H },
			{ "i" , GLFW_KEY_I },
			{ "j" , GLFW_KEY_J },
			{ "k" , GLFW_KEY_K },
			{ "l" , GLFW_KEY_L },
			{ "m" , GLFW_KEY_M },
			{ "n" , GLFW_KEY_N },
			{ "o" , GLFW_KEY_O },
			{ "p" , GLFW_KEY_P },
			{ "q" , GLFW_KEY_Q },
			{ "r" , GLFW_KEY_R },
			{ "s" , GLFW_KEY_S },
			{ "t" , GLFW_KEY_T },
			{ "u" , GLFW_KEY_U },
			{ "v" , GLFW_KEY_V },
			{ "w" , GLFW_KEY_W },
			{ "x" , GLFW_KEY_X },
			{ "y" , GLFW_KEY_Y },
			{ "z" , GLFW_KEY_Z },//numbers
			{ "0" , GLFW_KEY_0 },
			{ "1" , GLFW_KEY_1 },
			{ "2" , GLFW_KEY_2 },
			{ "3" , GLFW_KEY_3 },
			{ "4" , GLFW_KEY_4 },
			{ "5" , GLFW_KEY_5 },
			{ "6" , GLFW_KEY_6 },
			{ "7" , GLFW_KEY_7 },
			{ "8" , GLFW_KEY_8 },
			{ "9" , GLFW_KEY_9 },
			{ "," , GLFW_KEY_COMMA },//other
			{ " " , GLFW_KEY_SPACE },
			{ "/" , GLFW_KEY_SLASH },
			{ "." , GLFW_KEY_PERIOD },
			{ "delete" , GLFW_KEY_BACKSPACE}, // delete last character
	}; // keymap
	// iterate using C++17 facilities
	
	for (const auto& n : k) {
		auto letter = n.first;
		auto value = n.second;
		if (glfwGetKey(window->window, value) == GLFW_PRESS) {
			
			if (letter == save_key and repeats < 10) { repeats++; return; }
			else if (repeats == 10) save_key = ""; repeats = 0;
			if (letter == "delete") {
				save_key = letter;
				*tlog = tlog->substr(0, tlog->size() - 1); logframes = 0;
				break;//remove last charachter from log
			}
			else {
				save_key = letter;
				tlog->append(letter); logframes = 0; break; // add character
			}
		}
	}

	time++;
	if (time == 25) {
		time = 0;
		if (showing == true) {
			showing = false;
		}
		else {
			showing = true;
		}
	}
	
}
void TextField::check_input() {
	glm::vec4 point = return_ndc_cursor(window->window);
	if (glfwGetMouseButton(window->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		bool was_clicked = panel->accept_input(point);
		if (was_clicked) was_initiated = true;
		else was_initiated = false;
	}
}

void TextField::render() {
	shader->use();
	std::string showing_text = *tlog;
	if (showing && was_initiated) {
		showing_text.append("|");
	}
	if (was_initiated) {
		shader->setBool("changeColor", true);
	}
	panel->render();
	shader->setBool("changeColor", false);

	antonio_bold->drawText(showing_text, posx - 95, posy, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
}