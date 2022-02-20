#include "Button.h"
#include "lowlevel/UTILITY.h"

void Button::change_position(double x, double y) {
	posx = x;
	posy = y;
}
void Button::setText(Text* font, std::string text, float scale, float R, float G, float B) {
	font->drawText(text, posx - 40, posy, scale, glm::vec3(R, G, B));
}
void Button::set_texture(std::string PATH) {
	texture = new TEXTURE(PATH);
}
Button::Button(Shader* _shader, WINDOW* _windowobj, double _posx, double _posy, double _scale, std::string PATH) {
	VAO = new VertexArrayObject(PATH.c_str());
	shader = _shader;
	windowobj = _windowobj;
	posx = _posx;
	posy = _posy;
	scale = _scale;
	frames = &frames__;
	
}

void Button::create_button(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO, TEXTURE* texture,
	double posx, double posy, double scale) {
	texture_shader->use();
	if (*frames > 10) { texture_shader->setBool("changeColor", false); this->change_color = false; *frames = 0; }
	else if (this->change_color) {
		/*
		NOTE: for some reason changing uniform works only from mainloop and only if its directly like this
		because the uniform should be updated every frame!
		should note for future button slots implementation

		*/
		texture_shader->setBool("changeColor", true);
		*frames = *frames + 1;
	}

	//rendering object1
	this->modl = texture_shader->transform(windowobj->window, posx, posy, scale);

	texture->use(); // pick texture
	VAO->use(); // pick vao
	DRAW(6); // draw 6 vertices
	texture_shader->setBool("changeColor", false);
}
void Button::render() {
	create_button(shader, windowobj, VAO, texture, posx, posy, scale);
}
bool Button::is_clicked() {
	accept_input(return_ndc_cursor(windowobj->window));
	if (this->clicked) {
		this->clicked = false;
		this->change_color = true;
		return true;
	}
	else return false;
}
void Button::accept_input(glm::vec4 point) {
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