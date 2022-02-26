// main header
#include "ClickEventCanceller.h"
// utility
#include "lowlevel/UTILITY.h"

//changes position on screen similar to Button class
void ClickEventCanceller::change_position(double x, double y) {
	posx = x;
	posy = y;
}
/*
* ClickEventCanceller constructor
*
* takes 6 arguments all neccesary
* Shader* _shader --> shader with which the object is rendered
* WINDOW* _windowobj --> window on which is rendered
* const char* path, --> path to texture
* double _posx, double _posy, double _scale --> screen coords and scale
*/
ClickEventCanceller::ClickEventCanceller(Shader* _shader, WINDOW* _windowobj, const char* path, double _posx, double _posy, double _scale) {
	shader = _shader;
	windowobj = _windowobj;
	posx = _posx;
	posy = _posy;
	scale = _scale;
	TEXTURE temp = TEXTURE(std::string(path));
	ID = temp.ID;
}
// creates a 'canceller' using class variables defined in constructor
void ClickEventCanceller::create_canceller(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO,
	double posx, double posy, double scale) {
	texture_shader->use();//pick shader
	//rendering object1
	this->model = texture_shader->transform(windowobj->window, posx, posy, scale); // 200 -xpos , 100 -ypos , 0.2 -scale;
	glBindTexture(GL_TEXTURE0, ID);// bind texture
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // turn polygon mode on because cancellers should not be solid (not neccesary)
	VAO->use();
	DRAW(6); // draw 6 vertices
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
// checks if the canceller should block or not ,
// returns true if yes , false otherwise
// similar to Button takes its 6 vertices and checks
bool ClickEventCanceller::should_block(glm::vec4 point) {
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
	else return false;
}
//renders the canceller on screen
void ClickEventCanceller::render() {
	create_canceller(shader, windowobj, &VAO, posx, posy, scale);
}