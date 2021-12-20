#include "MAINWIN.h"


int main() {
	MAINWIN* window = new MAINWIN(500, 500);
	window->ConfigOpenGL();
	window->CreateShaderProgram("D:\\Visual Studio\\Projects\\OPENGL_PROJECT\\VERTEXSHADER.glsl"
		, "D:\\Visual Studio\\Projects\\OPENGL_PROJECT\\FRAGMENTSHADER.glsl");
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};
	window->ConfigDrawing(vertices);
	while (!glfwWindowShouldClose(window->get_window())) {
		window->processinput(window->get_window());
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window->get_window());
		glfwPollEvents();

	}
	glfwTerminate();
	delete window;
	return 0;
}