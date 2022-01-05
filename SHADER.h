#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

std::string get_file_contents(const char* filename);

class Shader
{
public:
    //for proccesinput
    int transformCalled = 0;
   
    std::vector<glm::mat4> model_;
    
    
   
	// Reference ID of the Shader Program
	GLuint ID;
    bool normalize = false;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();
    //influences below methods
    bool NORMALIZE_VALUES();
    // VERTEXSHADER uniform dependant

   
    void color(float R, float G, float B, float A);
    void transform(GLFWwindow* window , float x, float y, float scale);
    


	GLuint return_ID() { return ID; }

    void use() const;
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const;
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const;
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const;
    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat) const;
private:
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};


#endif