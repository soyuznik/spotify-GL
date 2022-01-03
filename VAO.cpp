#include "VAO.h"


std::vector<float> VertexArrayObject::load_vertices() {
    std::vector<float> vectVertices;
    std::string line; int line_number = -1;
    std::ifstream loadv(PATH.c_str());
    while (getline(loadv, line)) {
        line_number++;
        std::string x, y, z , tx , ty;
        std::stringstream str(line);
        str >> x; str >> y; str >> z; str >> tx; str >> ty;
        auto n = line.find("//");
        if (n != std::string::npos)
        {
            line.erase(n, 120);
        }
        try {
            vectVertices.push_back(stof(x));
            vectVertices.push_back(stof(y));
            vectVertices.push_back(stof(z));
            vectVertices.push_back(stof(tx));
            vectVertices.push_back(stof(ty));

            vertices_vec4.push_back(glm::vec3(stof(x), stof(y), stof(z)));
        }
        catch (...) {
            std::cout << "ERROR::MAIN::load_vertices , failed to convert string to float on line  " << line_number;
            throw std::invalid_argument("failed to convert string to float");
        }
    }
    return vectVertices;


}
VertexArrayObject::VertexArrayObject(const char* argPATH){
    PATH = argPATH;
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<float> vertices = this->load_vertices();

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

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
