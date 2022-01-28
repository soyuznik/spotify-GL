#include "ListObject.h"
#include "lowlevel/UTILITY.h"

void ListObject::update_scroll_info(double offset) {
	for (int j = 0; j < yaxis_offset.size(); j++) {
		yaxis_offset[j] = offset;
	}
}
void ListObject::manage_scroll() {
	for (int io = 0; io < buttons.size(); io++) {
		Button* dereferenced_button = buttons[io];
		dereferenced_button->change_position(dereferenced_button->posx, (dereferenced_button->posy +
			(list_sensitivity * yaxis_offset[io]))); yaxis_offset[io] = 0;
	}

	

}
ListObject::ListObject(Shader* texture_shader_ , WINDOW* window_ , double xpos_, double ypos_ , double scale_) {
	texture_shader = texture_shader_;
	window = window_;
	xpos = xpos_;
	ypos = ypos_;
	scale = scale_;
	glfwSetWindowUserPointer(window->window, this);
	
	antonio_bold = new Text(*window, "fonts/Antonio-Bold.ttf");
	ClickEventCanceller* canceller = new ClickEventCanceller(texture_shader, window, "textures/container.jpg", xpos, ypos, scale + 0.01);
	ClickEventCanceller* canceller1 = new ClickEventCanceller(texture_shader, window, "textures/container.jpg", xpos, ypos - 670, scale + 0.01);
	cancellers.push_back(canceller);
	cancellers.push_back(canceller1);
}
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
void ListObject::add_item(std::string ItemText) {
	static int items = 0; items++;
	Button* button = new Button(texture_shader, window, 832, (280 + (items * 50)), 0.2, items-1, "vertices/square_wider.buf");
	ButtonTexts.push_back(ItemText);
	buttons.push_back(button);
	yaxis_offset.push_back(0);
}
void ListObject::render() {
	bool is_point_inside_blocker = false;
	glm::vec4 point = return_ndc_cursor(window->window);
	for (int ix = 0; ix < cancellers.size(); ix++) {
		ClickEventCanceller tempcl = *cancellers[ix];
		tempcl.render();
		if (tempcl.should_block(point)) {
			is_point_inside_blocker = true;
		}
	}
	for (int ix = 0; ix < buttons.size(); ix++) {
		Button tempbt = *buttons[ix];
		tempbt.render();
		tempbt.setText(antonio_bold, ButtonTexts[ix], 0.4f);
		if (glfwGetMouseButton(window->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !is_point_inside_blocker) {
			tempbt.accept_input(point, ix);
		}	
	}
}