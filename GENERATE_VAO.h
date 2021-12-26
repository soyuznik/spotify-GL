#pragma once
#include "CONFIG_GL.h"


class GENERATE_VAO
{
public:
	std::string PATH;
	std::vector<float> load_vertices();
	GENERATE_VAO(const char* PATH);
	unsigned int return_VAO();
};

