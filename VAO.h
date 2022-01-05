#pragma once
#include "WINDOW.h"


class VertexArrayObject
{
public:
	std::vector<glm::vec3> return_data(std::vector<std::vector<glm::vec3>> VAOs_vector);
	std::vector<float> s_vector;
	std::vector<float> v_vector;
	std::vector<glm::vec3> vec4_vector;
	bool normalize;
	std::string PATH;
	unsigned int ID;

	void load_vertices();
	VertexArrayObject(const char* argPATH);
	void use();
	
};

