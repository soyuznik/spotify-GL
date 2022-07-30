// main header
#include "TextField.h"
//utility
#include "lowlevel/UTILITY.h"
#include "clipboardxx.hpp"


#define __TEXTFIELD_DEFINE_KEYMAP std::map<std::string, int> k{             \
			{ "a", GLFW_KEY_A},   /* letters*/                              \
			{ "b" , GLFW_KEY_B },								            \
			{ "c" , GLFW_KEY_C },								            \
			{ "d" , GLFW_KEY_D },								            \
			{ "e" , GLFW_KEY_E },								            \
			{ "f" , GLFW_KEY_F },								            \
			{ "g" , GLFW_KEY_G },								            \
			{ "h" , GLFW_KEY_H },								            \
			{ "i" , GLFW_KEY_I },								            \
			{ "j" , GLFW_KEY_J },								            \
			{ "k" , GLFW_KEY_K },								            \
			{ "l" , GLFW_KEY_L },								            \
			{ "m" , GLFW_KEY_M },								            \
			{ "n" , GLFW_KEY_N },								            \
			{ "o" , GLFW_KEY_O },								            \
			{ "p" , GLFW_KEY_P },								            \
			{ "q" , GLFW_KEY_Q },								            \
			{ "r" , GLFW_KEY_R },								            \
			{ "s" , GLFW_KEY_S },								            \
			{ "t" , GLFW_KEY_T },								            \
			{ "u" , GLFW_KEY_U },								            \
			{ "v" , GLFW_KEY_V },								            \
			{ "w" , GLFW_KEY_W },								            \
			{ "x" , GLFW_KEY_X },								            \
			{ "y" , GLFW_KEY_Y },								            \
			{ "z" , GLFW_KEY_Z },/*numbers*/					            \
			{ "0" , GLFW_KEY_0 },								            \
			{ "1" , GLFW_KEY_1 },								            \
			{ "2" , GLFW_KEY_2 },								            \
			{ "3" , GLFW_KEY_3 },								            \
			{ "4" , GLFW_KEY_4 },								            \
			{ "5" , GLFW_KEY_5 },								            \
			{ "6" , GLFW_KEY_6 },								            \
			{ "7" , GLFW_KEY_7 },								            \
			{ "8" , GLFW_KEY_8 },								            \
			{ "9" , GLFW_KEY_9 },								            \
			{ "," , GLFW_KEY_COMMA },/*other	*/				            \
			{ " " , GLFW_KEY_SPACE },							            \
			{ "/" , GLFW_KEY_SLASH },							            \
			{ "." , GLFW_KEY_PERIOD },							            \
			{ "delete" , GLFW_KEY_BACKSPACE }, /* delete last character*/   \
            };   


//textfield constructor
/* takes 4 args
Shader* shader_, ---> shader to render
WINDOW* window_, ---> window on which to render
double posx_, --> posx and y
double posy_

*/
TextField::TextField(Shader* shader_, WINDOW* window_, double posx_, double posy_) {
	shader = shader_;
	window = window_;
	posx = posx_;
	posy = posy_;

	Panel* panel__ = new Panel(shader, window, "Resources/textures/transparent_searchbar.png", posx + 100, posy, 0.15f , "Resources/vertices/square_textfield.buf");

	///////////////// Custom font creation //////////////////////////
	// https://www.glyphrstudio.com/online/
	// https://cloudconvert.com/otf-to-ttf
	Text* antonio_bold__ = new Text(*window, "Resources/fonts/Arial-Sans.ttf");
	panel = panel__;
	antonio_bold = antonio_bold__;
}

// returts the text taht is currently displayed on TEXTFIELD
std::string TextField::text() {
	std::string text__ = *tlog;
	return text__;
}
bool is_ClipboardActive = false;
// LOGS keys pressed by user
void TextField::logkey() {
	/* ======== ENTER LOG SCOPE ---> */ {
	if (!was_initiated) return;
	__TEXTFIELD_DEFINE_KEYMAP

		// iterate using C++17 facilities
		if (glfwGetKey(window->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS and glfwGetKey(window->window, GLFW_KEY_V) == GLFW_PRESS and !is_ClipboardActive) {
			is_ClipboardActive = true;
			clipboardxx::clipboard clipboardobj;
			std::string clipboard;
			clipboardobj >> clipboard;
			tlog->append(clipboard);
			return;
		}
	if (glfwGetKey(window->window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE or glfwGetKey(window->window, GLFW_KEY_V) == GLFW_RELEASE and is_ClipboardActive) {
		is_ClipboardActive = false;

	}
	
	for (const std::pair<const std::string, int>& n : k) {
		std::string letter = n.first;
		int value = n.second;

		if (glfwGetKey(window->window, value) == GLFW_PRESS) {
            if (letter == save_key and repeats < 30) { repeats++; return; } // if holding cause delay
			else if (save_key != letter) { save_key = letter; repeats = 0; } // if changed letter = no delay
			
			if (letter == "delete") {
				save_key = letter;
				*tlog = tlog->substr(0, tlog->size() - 1); 
				logframes = 0;
				break;//remove last character from log
			}
			else {
				tlog->append(letter); logframes = 0; break; // add character

			}
		}
	}
	}/* <------- EXIT LOG SCOPE ===== */

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
void TextField::__POSTEVENT_logkey() { // if press and release key , add letter
	//__TEXTFIELD_DEFINE_KEYMAP
   // if (glfwGetKey(window->window, k[save_key]) == GLFW_RELEASE && logframes == 0) {
		//if (save_key == "delete") {
	//		*tlog = tlog->substr(0, tlog->size() - 1);
	//		logframes = 1;
			//remove last character from log
	//	}
	//	else {
	//		tlog->append(save_key); logframes = 0;// add character
	//	}
	//}
}
// checks if user initiated the TEXTFIELD --- *turns gray*
void TextField::check_input() {
	glm::vec4 point = return_ndc_cursor(window->window);
	if (glfwGetMouseButton(window->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		bool was_clicked = panel->accept_input(point);
		if (was_clicked) was_initiated = true;
		else was_initiated = false;
	}
}

// rendering the textfield
void TextField::render() {
	
	shader->use();
	std::string showing_text = *tlog;
	if (showing_text.size() > 32) {
		showing_text.erase(0, (showing_text.size() - 32));
	}
	if (showing && was_initiated) {
		showing_text.append("|");
	}
	if (was_initiated) {
		shader->setBool("changeColor", true);
	}
	if (was_initiated) {
		
		panel->ID = activeID;
	}
	else if (!was_initiated && !showing_text.empty()) {

		panel->ID = activeID;
	}
	else {
		panel->ID = unactiveID;
	}
	panel->render();
	shader->setBool("changeColor", false);

	antonio_bold->drawText(showing_text, posx - 11, posy - 10, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f)); // drawing text
}

