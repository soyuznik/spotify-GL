#pragma once


// iostream idk for strings maybe or "cout"
#include <iostream>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
// glfw for context which openGL need to draw in like a canvas
#include <GLFW/glfw3.h>
//type conversion
#include <string>

//other utility
#include <windows.h>
#include <fstream>
#include <sstream>

//macros
#define INSTANT_MOUSE_CALLBACK false



class MAINWIN
{   public:
	    unsigned int ID = 0;
	    MAINWIN(int w , int h);
		void ConfigOpenGL();
		GLFWwindow* window;
		void processinput(GLFWwindow* window);
		void CreateShaderProgram(const char* vertexPath, const char* fragmentPath);
        void checkCompileErrors(unsigned int shader, std::string type);
        void ConfigDrawing(float vertices[]);

        // activate the shader
        void use();
        
        void setBool(const std::string& name, bool value) const;
           
        void setInt(const std::string& name, int value) const;
         
        void setFloat(const std::string& name, float value)const;
        
        GLFWwindow* get_window() { return window; }
       private:
		 int windowSizeW;
		 int windowSizeH;
		 std::string WINname;
		 



};


