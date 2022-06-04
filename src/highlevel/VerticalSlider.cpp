#include "VerticalSlider.h"
// utility
#include "lowlevel/UTILITY.h"
//for isnan()
#include <math.h>




inline double is_in_sliderM(double value) {
	if (value < -0.515) {
		value = -0.515;
	}
	if (value > 0.72) {
		value = 0.72;
	}
	return value;
}




// changes position on screen
void VerticalSlider::change_position(double x, double y) {
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
VerticalSlider::VerticalSlider(Shader* _shader, WINDOW* _windowobj, const char* path, double _posx, double _posy, double _scale) {
	shader = _shader;
	windowobj = _windowobj;
	posx = _posx;
	posy = _posy;
	scale = _scale;
	txcounter = new Text(*windowobj, "Resources/fonts/Antonio-Light.ttf");



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
// returns dot postion based on song lengh
double VerticalSlider::return_pos(double song_lenght) {
	double pos = (this->setdotpos + 0.5) * song_lenght;
	return pos;
}
// sets dot postion at <seconds> position , and <song_lenght> sample lengh
void VerticalSlider::set_pos(double seconds, double song_lenght) {
	crtsongtime = seconds;
	fullsongtime = song_lenght;
	this->setdotpos = (seconds / song_lenght) - 0.5;
	if (isnan(this->setdotpos)) {
		this->setdotpos = -1; // if is nan this->setdotpos 
		//will be reduced to -0.5 by is_in_slider , any value < -0.5 is good...
	}
	this->setdotpos = is_in_slider(this->setdotpos);
}
// creates a SLIDER using class variables
void VerticalSlider::create_panel(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO,
	double posx, double posy, double scale) {
	texture_shader->use();
	//rendering object1
	this->model = texture_shader->transform(windowobj->window, posx, posy, scale); // 200 -xpos , 100 -ypos , 0.2 -scale;
	glBindTexture(GL_TEXTURE_2D, ID);// pick texture
	VAO->use(); // pick vao
	DRAW(6); // draw 6 vertices
	//x = x / width * 2 - 1;
	// transform just y
	texture_shader->not_normaltransformM(windowobj->window, posx, this->setdotpos, 0.03f);
	//dot drawing
	//texture_shader->notnormal_transform(windowobj->window, posx, posy, 1.03f);
	dotTexture.use();
	DOT.use();
	DRAW(6);

}
// accepts  user input
bool VerticalSlider::accept_input(glm::vec4 point) {
	std::vector<glm::vec3> raw = VAO.vec4_vector;
	glm::vec4 A = this->model * glm::vec4(raw[0], 1.0f);
	glm::vec4 B = this->model * glm::vec4(raw[1], 1.0f);
	glm::vec4 C = this->model * glm::vec4(raw[2], 1.0f);
	glm::vec4 A1 = this->model * glm::vec4(raw[3], 1.0f);
	glm::vec4 B1 = this->model * glm::vec4(raw[4], 1.0f);
	glm::vec4 C1 = this->model * glm::vec4(raw[5], 1.0f);

	if (isInTriangle(A, B, C, point) or isInTriangle(A1, B1, C1, point)) {
		double value = is_in_sliderM(point.y);
		if (dposy != value) {
			this->setdotpos = value;
		}
		return true;
	}
	return false;
}
// create_panel invoker
void VerticalSlider::render() {
	create_panel(shader, windowobj, &VAO, posx, posy, scale);
}
