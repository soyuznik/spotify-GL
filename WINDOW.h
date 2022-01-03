#pragma once
// including glad used for shaders etc to configure them
#include <glad/glad.h>
// iostream idk for strings maybe or "cout"
//glm for mat4... etc
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
// cout , I/O
#include <iostream>
// glfw for context which openGL need to draw in like a canvas
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <vector>


#define TRANSPARENT_INSTANT 0
#define TRANSPARENT_WINDOW 1
#define TRANSPARENT_WINDOW_STATIC 3
#define TRANSPARENT_NO 2
float distance(float x1, float y1, float x2, float y2);
float calc_area(float a, float b, float c);
int position(float area, float A, float B, float C);
void calc(float x1, float y1, float x2, float y2
	, float x3, float y3, float x, float y, int* flag, float* area);
bool isInTriangle(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 point);

class WINDOW{
public:

	GLFWwindow* window;
	GLFWmonitor** monitors;
	const GLFWvidmode* videoMode;
	// here some stuff i dont understand xd but i think it sets the aspect ratio and monitor stuff
	int count, windowWidth, windowHeight, monitorX, monitorY;
	// window size
	int windowSizeW = 640, windowSizeH = 480;
	WINDOW(int transparency);
	void CONFIG_MONITOR();
	GLFWwindow* DEFINE_WINDOW(int transparency);
	void processinput(std::vector<glm::vec3> data);


};


