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
#include "SHADER.h"

#define TRANSPARENT_INSTANT 0
#define TRANSPARENT_WINDOW 1
#define TRANSPARENT_WINDOW_STATIC 3
#define TRANSPARENT_NO 2


class WINDOW{
public:
	
	GLFWwindow* window;
	GLFWmonitor** monitors;
	const GLFWvidmode* videoMode;
	// here some stuff i dont understand xd but i think it sets the aspect ratio and monitor stuff
	int count, windowWidth, windowHeight, monitorX, monitorY;
	// window size
	int windowSizeW = 640, windowSizeH = 480;
	WINDOW(int transparency , int width , int height);
	void CONFIG_MONITOR();
	GLFWwindow* DEFINE_WINDOW(int transparency);
	void processinput(std::vector<glm::vec3> data , Shader shader);


};

