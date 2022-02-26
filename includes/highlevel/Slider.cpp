#include "Slider.h"
#include "lowlevel/UTILITY.h"
void Slider::change_position(double x, double y) {
	posx = x;
	posy = y;
}
Slider::Slider(Shader* _shader, WINDOW* _windowobj, const char* path, double _posx, double _posy, double _scale) {
	shader = _shader;
	windowobj = _windowobj;
	posx = _posx;
	posy = _posy;
	scale = _scale;


	dposy = _posy;
	dposx = _posx - 237;
	int width, height;
	glfwGetWindowSize(windowobj->window, &width, &height);
	dposx = dposx / width * 2 - 1;
	dposy = dposy / height * 2 - 1;
	
	dscale = 0.03f;
	TEXTURE* temp = new TEXTURE(std::string(path));
	ID = temp->ID;
}
double Slider::return_pos(double song_lenght) {
	double pos = (this->setdotpos + 0.5) * song_lenght;
	return pos;
}
void Slider::set_pos(double seconds , double song_lenght) {
	this->setdotpos = (seconds / song_lenght) - 0.5;
	this->setdotpos = is_in_slider(this->setdotpos);
	
}
void Slider::create_panel(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO,
	double posx, double posy, double scale) {
	texture_shader->use();
	//rendering object1
	texture_shader->transform(windowobj->window, posx, posy, scale); // 200 -xpos , 100 -ypos , 0.2 -scale;
	glBindTexture(GL_TEXTURE_2D, ID);// pick texture
	VAO->use(); // pick vao
	DRAW(6); // draw 6 vertices
	this->model = texture_shader->transform(windowobj->window, posx, posy, scale + 0.05f); 
	//dot drawing 
	texture_shader->notnormal_transform(windowobj->window, this->setdotpos, dposy, 0.03f);
	DOT.use();
	DRAW(6);
}

bool Slider::accept_input(glm::vec4 point) {
	std::vector<glm::vec3> raw = VAO.vec4_vector;
	glm::vec4 A = this->model * glm::vec4(raw[0], 1.0f);
	glm::vec4 B = this->model * glm::vec4(raw[1], 1.0f);
	glm::vec4 C = this->model * glm::vec4(raw[2], 1.0f);
	glm::vec4 A1 = this->model * glm::vec4(raw[3], 1.0f);
	glm::vec4 B1 = this->model * glm::vec4(raw[4], 1.0f);
	glm::vec4 C1 = this->model * glm::vec4(raw[5], 1.0f);

	if (isInTriangle(A, B, C, point) or isInTriangle(A1, B1, C1, point)) {
		double value = is_in_slider(point.x);
		if (dposx != value) {
			this->setdotpos = value;
			
		}
		return true;
	}
	return false;
}

void Slider::render() {
	create_panel(shader, windowobj, &VAO, posx, posy, scale);
}
void Slider::setText(Text* font, std::string text, float scale, float R, float G, float B) {
	font->drawText(text, posx - 40, posy, scale, glm::vec3(R, G, B));
}