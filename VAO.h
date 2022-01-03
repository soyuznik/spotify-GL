#pragma once
#include "WINDOW.h"


class VertexArrayObject
{
public:
	std::string PATH;
	unsigned int ID;
	std::vector<glm::vec3> vertices_vec4;
	std::vector<float> load_vertices();
	VertexArrayObject(const char* argPATH);
	void use();
	
};

