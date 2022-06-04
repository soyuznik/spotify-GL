// main header
#include "ListObject.h"
//utility
#include "lowlevel/UTILITY.h"

//manages the scroll of each button in a vector
void ListObject::update_scroll_info(double offset) {
	for (int j = 0; j < yaxis_offset.size(); j++) {
		yaxis_offset[j] = offset;
	}
}
// changed button position based on yaxis_offset vector
void ListObject::manage_scroll() {
	for (int io = 0; io < buttons.size(); io++) {
		ListButton* dereferenced_button = buttons[io];
		dereferenced_button->change_position(dereferenced_button->posx, (dereferenced_button->posy +
			(list_sensitivity * yaxis_offset[io]))); yaxis_offset[io] = 0;
	}
}
//ListObject Constructor
/*
Takes 5 arguments all neccesary...
Shader* texture_shader_, --> shader with witch the list is rendered
WINDOW* window_, --> window on which the list is rendered
double xpos_, double ypos_, double scale_ ---> positions and scale on window
*/
ListObject::ListObject(Shader* texture_shader_, WINDOW* window_, double xpos_, double ypos_, double scale_) {
	texture_shader = texture_shader_;
	window = window_;
	xpos = xpos_;
	ypos = ypos_;
	scale = scale_;
	// special pointer so the list works , can be accesed through GLFWwindow*
	glfwSetWindowUserPointer(window->window, this);

	antonio_bold = new Text(*window, "Resources/fonts/OpenSans-Regular.ttf");
	/// created cancellers based on coords
	ClickEventCanceller* canceller = new ClickEventCanceller(texture_shader, window, "Resources/textures/container.jpg", xpos, ypos, scale + 0.01);
	ClickEventCanceller* canceller1 = new ClickEventCanceller(texture_shader, window, "Resources/textures/container.jpg", xpos, ypos - 623, scale + 0.01);
	cancellers.push_back(canceller);
	cancellers.push_back(canceller1);
}
// returns all Buttons VAO vertices *DEPRECATED*
std::vector<glm::vec3> ListObject::return_clickable_data() {
	//creating a vector with objects that need to do something when clicked
	std::vector<std::vector<glm::vec3>> VAOs_that_need_input_slots;
	for (unsigned int i = 0; i < buttons.size(); i++) {
		VAOs_that_need_input_slots.push_back(buttons[i]->VAO->vec4_vector);
	}
	//<VAO.return_data> is used to merge VAO's vectors into 1 (data)
	std::vector<glm::vec3> data = buttons[0]->VAO->return_data(VAOs_that_need_input_slots);
	return data;
}
// returns all Cancellers VAO vertices *DEPRECATED*
std::vector<glm::vec3> ListObject::return_blocking_data() {
	//outlayer
	std::vector<std::vector<glm::vec3>> VAOs_that_need_to_block_clicks;
	for (unsigned int i = 0; i < cancellers.size(); i++) {
		ClickEventCanceller cancel = *cancellers[i];
		VAOs_that_need_to_block_clicks.push_back(cancel.VAO.vec4_vector);
	}
	std::vector<glm::vec3> data_for_blocking = buttons[0]->VAO->return_data(VAOs_that_need_to_block_clicks);
	return data_for_blocking;
}

// Adds a item with custom txt on the list , return pointer to the button
ListButton* ListObject::add_item(std::string ItemText) {
	static int items = 0; items++;   /////////////////////////// items * offset bettween buttons in list
	ListButton* button = new ListButton(texture_shader, window, xpos, (280 + (items * 55)), 0.2, "Resources/vertices/square_wider_list.buf");
	ButtonTexts.push_back(ItemText);
	buttons.push_back(button);
	yaxis_offset.push_back(0);

	return button;
}

// renders the List on screen
// returns null if there is no Button or is inside a canceller
ListButton* ListObject::render_and_manage_input() {
	bool is_point_inside_blocker = false; //creates a bool for blocking
	ListButton* return_value = NULL; // the current return value
	glm::vec4 point = return_ndc_cursor(window->window); // cursor position

	//checks if the point is inside any canceller
	for (int ix = 0; ix < cancellers.size(); ix++) {
		ClickEventCanceller* tempcl = cancellers[ix];
		tempcl->render();
		if (tempcl->should_block(point)) {
			is_point_inside_blocker = true;
		}
	}
	//checks if point is inside any button
	for (int ix = 0; ix < buttons.size(); ix++) {
		ListButton* tempbt = buttons[ix];
		tempbt->render();
		tempbt->setText(antonio_bold, ButtonTexts[ix], 0.4f);
		if (glfwGetMouseButton(window->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !is_point_inside_blocker) {
			if (tempbt->is_clicked()) {
				return_value = tempbt;
			}
		}
	}
	return return_value; // returns null if there is no Button or is inside a canceller
}