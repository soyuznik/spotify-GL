#pragma once

// including glad used for shaders etc to configure them
#include <glad/glad.h>
// iostream idk for strings maybe or "cout"
#include <iostream>
// glfw for context which openGL need to draw in like a canvas
#include <GLFW/glfw3.h>


class CONFIG_GL
{
public:
	// window size
	int windowSizeW = 640, windowSizeH = 480;
	CONFIG_GL();
    GLFWwindow* DEFINE_WINDOW();

};

