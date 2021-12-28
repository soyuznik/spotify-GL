#pragma once
#include "CONFIG_GL.h"


class VertexArrayObject
{
public:
	std::string PATH;
	unsigned int ID;
	std::vector<float> load_vertices();
	VertexArrayObject(const char* argPATH);
	void use();
	
};

