#include "Checkbox.h"
#include "lowlevel/UTILITY.h"

void Checkbox::set_active(std::string active_path) {
	delete _t_active;
	_t_active = new TEXTURE(active_path);
	if (_t_active == NULL) {
		throw("Failed to load Texture CheckBox::set_active");
	}
}
void Checkbox::set_unactive(std::string unactive_path) {
	delete _t_unactive;
	_t_unactive = new TEXTURE(unactive_path);
	if (_t_unactive == NULL) {
		throw("Failed to load Texture CheckBox::set_unactive");
	}

}

Checkbox::Checkbox(Shader* _shader, WINDOW* _windowobj, double _posx, double _posy, double _scale , std::string PATH){
	VAO = new VertexArrayObject(PATH.c_str());
	shader = _shader;
	windowobj = _windowobj;
	posx = _posx;
	posy = _posy;
	scale = _scale;
	frames = &frames__;
}


// change position on screen
void Checkbox::change_position(double x, double y) {
	posx = x;
	posy = y;
}
//set text
void Checkbox::setText(Text* font, std::string text, float scale, float R, float G, float B) {
	font->drawText(text, posx - 40, posy, scale, glm::vec3(R, G, B));
}
//set text* custom for menu
void Checkbox::setTextM(Text* font, std::string text, float scale, float R, float G, float B) {
	font->drawText(text, posx - 110, posy - 15, scale, glm::vec3(R, G, B));
}
//set texture
void Checkbox::set_texture(std::string PATH) {
	texture = new TEXTURE(PATH);
}

// renders the button on screen using class variables from constructor
void Checkbox::create_button(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO, TEXTURE* texture,
	double posx, double posy, double scale) {
	if (_t_active == NULL or _t_unactive == NULL) {
		throw("No active/unactive textures to render! You Probably forgot to set it using check->set_active/unactive!");
	}
	if (active) texture = _t_active;
	if (!active) texture = _t_unactive;
	texture_shader->use(); // selecting shader
	/*
	...Here we change uniform so when the button is clicked it changes colors for ~ 10 'frames'

	*/
	//if (glfwGetMouseButton(windowobj->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	//{ texture_shader->setBool("changeColor", false); this->change_color = false;}
	if (this->change_color) {
		/*
		NOTE: for some reason changing uniform works only from mainloop and only if its directly like this
		because the uniform should be updated every frame!
		should note for future button slots implementation

		*/
		texture_shader->setBool("changeColor", true);
	}
	this->change_color = false;
	//rendering object1
	this->modl = texture_shader->transform(windowobj->window, posx, posy, scale);

	texture->use(); // pick texture
	VAO->use(); // pick vao
	DRAW(6); // draw 6 vertices
	texture_shader->setBool("changeColor", false); // dont change color for the rest of the rendering
}
bool Checkbox::is_active() {
	return this->active;
}
void Checkbox::set_activebool(bool __active) {
	this->active = __active;
}
void Checkbox::indent(std::string ident) {
	obj_ident = ident;
}
// creates button with class variables
void Checkbox::render() {
	create_button(shader, windowobj, VAO, texture, posx, posy, scale);
}
//checks if button is clicked using NDC coords
// true if clicked , false otherwise
bool Checkbox::is_clicked() {
	accept_input(return_ndc_cursor(windowobj->window));
	if (this->clicked and !(glfwGetMouseButton(windowobj->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)) {
		Sleep(100);
		active = !active;
	}
	if (this->clicked and (glfwGetMouseButton(windowobj->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)) {
		//active = !active;
		this->clicked = false;
		//this->change_color = true;
		return true;
	}
	else return false;
}
/*
-- Takes 1 argument , which is a point on screen

... then it takes all the vertices from the square-shaped button and checks if it contains it.
*/
void Checkbox::accept_input(glm::vec4 point) {
	std::vector<glm::vec3> raw = VAO->vec4_vector;
	glm::vec4 A = this->modl * glm::vec4(raw[0], 1.0f);
	glm::vec4 B = this->modl * glm::vec4(raw[1], 1.0f);
	glm::vec4 C = this->modl * glm::vec4(raw[2], 1.0f);
	glm::vec4 A1 = this->modl * glm::vec4(raw[3], 1.0f);
	glm::vec4 B1 = this->modl * glm::vec4(raw[4], 1.0f);
	glm::vec4 C1 = this->modl * glm::vec4(raw[5], 1.0f);

	if (isInTriangle(A, B, C, point) or isInTriangle(A1, B1, C1, point)) {
		this->clicked = true;
	}
}