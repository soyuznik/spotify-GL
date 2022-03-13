//main header
#include "Button.h"
//utility like return_ndc_cursor()
#include "lowlevel/UTILITY.h"
// change position on screen
void Button::change_position(double x, double y) {
	posx = x;
	posy = y;
}
//set text
void Button::setText(Text* font, std::string text, float scale, float R, float G, float B) {
	font->drawText(text, posx - 40, posy, scale, glm::vec3(R, G, B));
}
//set text* custom for menu
void Button::setTextM(Text* font, std::string text, float scale, float R, float G, float B) {
	font->drawText(text, posx - 110, posy - 15, scale, glm::vec3(R, G, B));
}
//set texture
void Button::set_texture(std::string PATH) {
	texture = new TEXTURE(PATH);
}
// button constructor
/* --- takes 6 args , 5 necessary
Shader* _shader --> shader that renders the button
WINDOW* _windowobj --> window on which the button is rendered
double _posx, double _posy, double _scale --> xpos , ypos on screen and scale used with a scaling matrix
 , std::string PATH (optional) set custom Vertex Array Buffer
*/
Button::Button(Shader* _shader, WINDOW* _windowobj, double _posx, double _posy, double _scale, std::string PATH) {
	VAO = new VertexArrayObject(PATH.c_str());
	shader = _shader;
	windowobj = _windowobj;
	posx = _posx;
	posy = _posy;
	scale = _scale;
	frames = &frames__;
}
// renders the button on screen using class variables from constructor
void Button::create_button(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO, TEXTURE* texture,
	double posx, double posy, double scale) {
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
// creates button with class variables
void Button::render() {
	create_button(shader, windowobj, VAO, texture, posx, posy, scale);
}
//checks if button is clicked using NDC coords
// true if clicked , false otherwise
bool Button::is_clicked() {
	accept_input(return_ndc_cursor(windowobj->window));
	if (this->clicked and !(glfwGetMouseButton(windowobj->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)) {
		this->clicked = false;
		this->change_color = true;
		return true;
	}
	else return false;
}
/*
-- Takes 1 argument , which is a point on screen

... then it takes all the vertices from the square-shaped button and checks if it contains it.
*/
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