#include "Panel.h"
#include "lowlevel/UTILITY.h"
void Panel::change_position(double x, double y) {
	posx = x;
	posy = y;
}
Panel::Panel(Shader* _shader, WINDOW* _windowobj, const char* path, double _posx, double _posy, double _scale) {
	shader = _shader;
	windowobj = _windowobj;
	posx = _posx;
	posy = _posy;
	scale = _scale;
	TEXTURE* temp = new TEXTURE(std::string(path));
	ID = temp->ID;
}

void Panel::create_panel(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO,
	double posx, double posy, double scale) {
	texture_shader->use();
	//rendering object1
	model = texture_shader->transform(windowobj->window, posx, posy, scale); // 200 -xpos , 100 -ypos , 0.2 -scale;
	glBindTexture(GL_TEXTURE_2D, ID);// pick texture
	VAO->use(); // pick vao
	DRAW(6); // draw 6 vertices
}
bool Panel::accept_input(glm::vec4 point) {
	std::vector<glm::vec3> raw = VAO.vec4_vector;
	glm::vec4 A = this->model * glm::vec4(raw[0], 1.0f);
	glm::vec4 B = this->model * glm::vec4(raw[1], 1.0f);
	glm::vec4 C = this->model * glm::vec4(raw[2], 1.0f);
	glm::vec4 A1 = this->model * glm::vec4(raw[3], 1.0f);
	glm::vec4 B1 = this->model * glm::vec4(raw[4], 1.0f);
	glm::vec4 C1 = this->model * glm::vec4(raw[5], 1.0f);

	if (isInTriangle(A, B, C, point) or isInTriangle(A1, B1, C1, point)) {
		return true;
	}
	return false;
}

void Panel::render() {
	create_panel(shader, windowobj, &VAO, posx, posy, scale);
}
void Panel::setText(Text* font, std::string text, float scale, float R, float G, float B) {
	font->drawText(text, posx - 40, posy, scale, glm::vec3(R, G, B));
}