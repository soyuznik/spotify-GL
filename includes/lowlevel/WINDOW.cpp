#include "WINDOW.h"
#include "highlevel/ListObject.h"
//for slots
#include <shellapi.h>
#include "UTILITY.h"
//used for the type of the window input *deprecated*
int INSTANT_MOUSE_CALLBACK;

//prototype that is defined later in the file
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void WINDOW::update_list_scroll(double offset) {
	for (int i = 0; i < yaxis_offset->size(); i++) {
		std::vector<int> yaxis_offset_temp;
		yaxis_offset_temp = *yaxis_offset;
		yaxis_offset_temp[i] = offset;
	}
}
//WINDOW constructor , <transparency> is a macro (see WINDOW.h)
WINDOW::WINDOW(int transparency, int width, int height) {
	// init glfw so we can use its things XD
	if (!glfwInit()) {
		std::cout << "FAILED TO LOAD GLFW\n";
		return;
	}
	windowSizeW = width;
	windowSizeH = height;
	this->DEFINE_WINDOW(transparency);
}
// used to config monitor for aspect ratio
void WINDOW::CONFIG_MONITOR() {
	// I am assuming that main monitor is in the 0 position
	monitors = glfwGetMonitors(&count);
	videoMode = glfwGetVideoMode(monitors[0]);
	// width: 75% of the screen
	windowWidth = static_cast<int>(videoMode->width / 1.5);
	// aspect ratio 16 to 9
	windowHeight = static_cast<int>(videoMode->height / 16 * 9);

	glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{ //only yoffset changes\\ - when down ; + when up
	ListObject* listobj = static_cast<ListObject*>(glfwGetWindowUserPointer(window));
	listobj->update_scroll_info(yoffset);
}
// will create a glfw window with the specified type (transparency)
GLFWwindow* WINDOW::DEFINE_WINDOW(int transparency) {
	this->CONFIG_MONITOR();
	bool hide_titlebar; // used for the type of the window specification
	switch (transparency) {
	case TRANSPARENT_WINDOW:
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // makes window transparent
		hide_titlebar = true; // hides titlebar when starting
		INSTANT_MOUSE_CALLBACK = 1; // sets input type response
		break;
	case TRANSPARENT_INSTANT:
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // makes window transparent
		hide_titlebar = true;
		INSTANT_MOUSE_CALLBACK = 0;
		break;
	case OPAQUE:
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE); // makes window opaque
		hide_titlebar = false; // will show title bar
		INSTANT_MOUSE_CALLBACK = 2;
		break;
	case TRANSPARENT_WINDOW_STATIC: // will make window transparent with  a titlebar
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
		hide_titlebar = false;
		INSTANT_MOUSE_CALLBACK = 3;
		break;
	default: //  in case of an invalid type will print valid types and throw a exception
		std::cout << "ERROR: CONFIG_GL::DEFINE_WINDOW::transparency\n"
			<< "#define TRANSPARENT_INSTANT 0\n"
			<< "#define TRANSPARENT_WINDOW 1\n"
			<< "#define TRANSPARENT_WINDOW_STATIC 3\n"
			<< "#define TRANSPARENT_NO 2\n";
		throw(GLFW_NO_WINDOW_CONTEXT);
	}

	/*  HERE IT SHOULD BE IN ORDER !!! 1. make window
									2. make the window current context
									3. load GLAD !*/
									// create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(windowSizeW, windowSizeH, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		std::cout << "FAILED TO LOAD WINDOW";
		return NULL;
	}

	// when window is clicked what it shoudl do
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// make the window's context current
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}

	// reset the window hints to default
	glfwDefaultWindowHints();
	// here we set the window pos on screen and because we divide the monitor resolution by 2 we get the middle coordinates
	glfwSetWindowPos(window,
		monitorX + (videoMode->width - windowWidth) / 2,
		monitorY + (videoMode->height - windowHeight) / 2);

	// show the window
	glfwShowWindow(window);

	// here we hide the titlebar based on the previous type
	if (hide_titlebar) {
		glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
	}
	else {
		glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
	}

	glfwSetScrollCallback(window, scroll_callback);

	return window; // returning GLFWwindow * window
}

void WINDOW::reserve_slots(int number) {
	for (unsigned int i = 0; i <= number; i++) {
		slot.push_back(false);
	}
}

void WINDOW::manage_slots(int triangle_number) {
	slot[triangle_number] = true;
	try {
		SLOTS(triangle_number);
	}
	catch (...) {
		throw("No SLOTS body defined");
	}
}
//the method that procceses all user input
void WINDOW::processinput(std::vector<glm::vec3> data, std::vector<glm::vec3> block_data, Shader shader) {
	int current_x, current_y; // saing current window position
	glfwGetWindowPos(window, &current_x, &current_y);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // quit with ESC
		glfwSetWindowShouldClose(window, true);

	// !!!*deprecated*!!! // enable key with comment
	bool use_wasd_window_movement = false;
	// independent keys
	if (use_wasd_window_movement) {
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			std::cout << std::to_string(xpos) + "," + std::to_string(ypos) << std::endl;
			// move up ^
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			glfwSetWindowPos(window, current_x, current_y - 5);
		// move down v
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			glfwSetWindowPos(window, current_x, current_y + 5);
		// <--- move left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			glfwSetWindowPos(window, current_x - 5, current_y);
		// more right --->
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			glfwSetWindowPos(window, current_x + 5, current_y);
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	static bool is_decorated = false;
	switch (INSTANT_MOUSE_CALLBACK) { // different mouse callback -> can be edited using the global macro
	case 0:
		static double _1xpos, _1ypos;// pos on 1st click
		static double _2xpos, _2ypos;// pos on 2nd click
		static double xoffset, yoffset;// how much should the window move on X and Y AXIS
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			glfwGetCursorPos(window, &_1xpos, &_1ypos); // setting 1st click pos
		}

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
			glfwGetCursorPos(window, &_2xpos, &_2ypos); // setting 2nd click pos

			// pool window move event
			xoffset = _2xpos - _1xpos; // offset (XY)
			yoffset = _2ypos - _1ypos;
			int currentx, currenty;
			glfwGetWindowPos(window, &currentx, &currenty);//window pos before updating
			glfwSetWindowPos(window, currentx + xoffset, currenty + yoffset);// setting new window position
		}
		break;

	case 1:

		if (is_decorated == false && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			glfwHideWindow(window);// hiding and showing to prevent weird visual bug
			glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE); // setting the decorated atribute so it shows the title bar
			glfwShowWindow(window);
			is_decorated = true;
		}
		else if (is_decorated == true && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			glfwHideWindow(window);
			glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);// setting the decorated atribute so it doesnt show the title bar
			glfwShowWindow(window);
			is_decorated = false;
		}
		break;
	case 2:
		break;
	}
}