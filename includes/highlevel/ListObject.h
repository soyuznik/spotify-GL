#pragma once
#include <string>
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

// higher level class
#include "highlevel/Button.h"
#include "highlevel/Panel.h"
#include "highlevel/ClickEventCanceller.h"

//ListObject class

class ListObject
{
public:
	std::vector<Button*> buttons; //vector with list buttons
	std::vector<ClickEventCanceller*> cancellers; // vector with its cancellers
	std::vector<std::string> ButtonTexts; // vector with the list buttons text

	// need to change this , because all buttons move the same
	// currently it changed the value of each button , based on the vector coords
	// but all values are the same
	std::vector<int> yaxis_offset;

	int list_sensitivity = 10; // sensitivity which list operates to
	Shader* texture_shader; // rendering shader
	WINDOW* window; // window on which is rendered
	double xpos;
	double ypos;
	double scale; // spacial positions
	Text* antonio_bold; // the text wich buttons are rendered
	ListObject(Shader* texture_shader, WINDOW* window, double xpos, double ypos, double scale);
	Button* add_item(std::string ItemText);
	Button* render_and_manage_input();

	//**DEPRECATED
	std::vector<glm::vec3> return_clickable_data();
	//**DEPRECATED
	std::vector<glm::vec3> return_blocking_data();
	void manage_scroll();
	void update_scroll_info(double offset);
};
