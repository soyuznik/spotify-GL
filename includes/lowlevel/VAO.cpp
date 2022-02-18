#include "VAO.h"
// concatenates all VAOs in the arg vector
std::vector<glm::vec3> VertexArrayObject::return_data(std::vector<std::vector<glm::vec3>> VAOs_vector) {
	if (VAOs_vector.size() == 1) { return VAOs_vector[0]; }
	std::vector<glm::vec3> data;
	for (unsigned int j = 0; j < (int)VAOs_vector.size() - 1; j++) {
		data.reserve(VAOs_vector[j].size() + VAOs_vector[j + 1].size()); // preallocate memory
		data.insert(data.end(), VAOs_vector[j].begin(), VAOs_vector[j].end());
		data.insert(data.end(), VAOs_vector[j + 1].begin(), VAOs_vector[j + 1].end());
	}
	return data;
}
// loads vertices from the path sprecified , each ending in a different vector based on flag (v , s , #)
void VertexArrayObject::load_vertices() {
	std::ifstream file(PATH);
	std::string line;
	while (getline(file, line)) {
		if (line.substr(0, 2) == "v ") {
			std::stringstream stream(line.substr(2));
			std::string x, y, z, tx, ty;
			stream >> x; stream >> y; stream >> z;
			stream >> tx; stream >> ty;

			v_vector.push_back(stof(x));
			v_vector.push_back(stof(y));
			v_vector.push_back(stof(z));
			v_vector.push_back(stof(tx));
			v_vector.push_back(stof(ty));

			vec4_vector.push_back(glm::vec3(stof(x), stof(y), stof(z)));
		}
		else if (line.substr(0, 1) == "#") {
			continue;
		}
		else if (line.substr(0, 2) == "s ") {
			std::stringstream stream(line.substr(2));
			std::string normalized, posx, posy, posz, scale;

			stream >> normalized; stream >> posx; stream >> posy;
			stream >> posz; stream >> scale;
			if (normalized == "true") {
				normalize = true;
			}
			else { normalize = false; }
			s_vector.push_back(stof(posx));
			s_vector.push_back(stof(posy));
			s_vector.push_back(stof(posz));
			s_vector.push_back(stof(scale));
		}
	}
}
VertexArrayObject::VertexArrayObject(const char* argPATH) {
	PATH = argPATH;
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	this->load_vertices();

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, v_vector.size() * sizeof(float), v_vector.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.

	ID = VAO;
	glBindVertexArray(0);
}
void VertexArrayObject::use() {
	glBindVertexArray(ID);
}