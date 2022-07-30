//main header
#include "highlevel/VolSlider.h"
// utility
#include "lowlevel/UTILITY.h"
//for isnan()
#include <math.h>



//volume
void VolSlider::set_volume(LoadAudio* aud) {
	aud->setVolume((setdotpos - 0.672) / 0.256);
}

// changes position on screen
void VolSlider::change_position(double x, double y) {
	posx = x;
	posy = y;
}
// slider constructor,
/*
Shader* _shader, --> shader to render
WINDOW* _windowobj,  --> window on which to render
const char* path, --> Texture path
double _posx, --- /
double _posy,   --   /   screen data
double _scale    --  /
*/
VolSlider::VolSlider(Shader* _shader, WINDOW* _windowobj, const char* path, double _posx, double _posy, double _scale) {
	shader = _shader;
	windowobj = _windowobj;
	posx = _posx;
	posy = _posy;
	scale = _scale;
	//txcounter = new Text(*windowobj, "fonts/Antonio-Light.ttf");



	dposy = _posy + 1;
	dposx = _posx - 237;
	int width, height;
	// NDC conversion
	glfwGetWindowSize(windowobj->window, &width, &height);
	dposx = dposx / width * 2 - 1;
	dposy = dposy / height * 2 - 1;

	dscale = 0.03f;
	TEXTURE* temp = new TEXTURE(std::string(path));
	ID = temp->ID;
}

// creates a SLIDER using class variables
void VolSlider::create_panel(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO,
	double posx, double posy, double scale) {

	texture_shader->use();
	texture_shader->setFloat("comparePosX", this->setdotpos);
	texture_shader->setBool("should_be_green", SHOW_DOT);
	//rendering object1
	this->model = texture_shader->transform(windowobj->window, posx, posy, scale); // 200 -xpos , 100 -ypos , 0.2 -scale;
	glBindTexture(GL_TEXTURE_2D, ID);// pick texture
	VAO->use(); // pick vao
	DRAW(6); // draw 6 vertices
	texture_shader->setFloat("comparePosX", -100);

	//dot drawing
	if (SHOW_DOT) {
		texture_shader->notnormal_transform(windowobj->window, this->setdotpos, dposy, 0.03f);
		dotTexture.use();
		DOT.use();
		DRAW(6);
	}
	//glm::vec3 white_clr = glm::vec3(1.0f, 1.0f, 1.0f);
	//std::string sngtime = std::to_string(fullsongtime / 60);
	//std::string curtime = std::to_string(crtsongtime / 60);// minute transformation
	//txcounter->drawText(curtime.erase(curtime.length() - 4, curtime.length()), posx - 267, posy - 2, 0.25f, white_clr);
	//txcounter->drawText(sngtime.erase(sngtime.length() - 4, sngtime.length()), posx + 250, posy - 2, 0.25f, white_clr);
}
// accepts  user input
bool VolSlider::accept_input(glm::vec4 point) {
	std::vector<glm::vec3> raw = VAO.vec4_vector;
	glm::vec4 A = this->model * glm::vec4(raw[0], 1.0f);
	glm::vec4 B = this->model * glm::vec4(raw[1], 1.0f);
	glm::vec4 C = this->model * glm::vec4(raw[2], 1.0f);
	glm::vec4 A1 = this->model * glm::vec4(raw[3], 1.0f);
	glm::vec4 B1 = this->model * glm::vec4(raw[4], 1.0f);
	glm::vec4 C1 = this->model * glm::vec4(raw[5], 1.0f);

	if (isInTriangle(A, B, C, point) or isInTriangle(A1, B1, C1, point)) {
		double value = point.x;
		if (value < 0.672) {
			value = 0.672;
		}
		if (value > 0.928) { // values at each end of the slider ---> need to be fixed
			value = 0.928;
		}
		if (point.x == value) {
			this->setdotpos = value; // setting according to slider position
		}




		return true;
	}
	return false;
}
bool VolSlider::accept_hover_input(glm::vec4 point) {
	std::vector<glm::vec3> raw = VAO.vec4_vector;
	glm::mat4 scaling = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 9.5f, 1.0f));
	glm::vec4 A = (this->model * scaling) * glm::vec4(raw[0], 1.0f);
	glm::vec4 B = (this->model * scaling) * glm::vec4(raw[1], 1.0f);
	glm::vec4 C = (this->model * scaling) * glm::vec4(raw[2], 1.0f);
	glm::vec4 A1 = (this->model * scaling) * glm::vec4(raw[3], 1.0f);
	glm::vec4 B1 = (this->model * scaling) * glm::vec4(raw[4], 1.0f);
	glm::vec4 C1 = (this->model * scaling) * glm::vec4(raw[5], 1.0f);

	if (isInTriangle(A, B, C, point) or isInTriangle(A1, B1, C1, point)) {
		//double value = is_in_slider(point.x);
		//if (dposx != value) {
		//	this->setdotpos = value;
		//}
		return true;
	}
	return false;
}
// create_panel invoker
void VolSlider::render() {
	create_panel(shader, windowobj, &VAO, posx, posy, scale);
}
