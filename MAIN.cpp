


#include "CONFIG_GL.h"
#include "SHADER.h"
#include "GENERATE_VAO.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




#include <iostream>
//input procces prototype
void processinput(GLFWwindow* window);



int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
    CONFIG_GL config;
    GLFWwindow* window = config.DEFINE_WINDOW(TRANSPARENT_WINDOW);


    Shader shader("VERTEXSHADER.glsl", "FRAGMENTSHADER.glsl");
    
    
    unsigned int VAO = GENERATE_VAO("vertices/triangle.buf").return_VAO();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // render
        processinput(window);
        shader.use();
        shader.setFloat("scale", 0.1f);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.5f ,0.5f ,0.0f));
        shader.setMat4("model", model);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need
        //to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // swap front and back buffers
        glfwSwapBuffers(window);

        // poll for and process events
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
void processinput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    int current_x, current_y;
    glfwGetWindowPos(window, &current_x, &current_y);




    // independent keys
    // move up ^
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glfwSetWindowPos(window, current_x, current_y - 5);
    // move down v
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        glfwSetWindowPos(window, current_x, current_y + 5);
    // <--- move left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        glfwSetWindowPos(window, current_x - 5, current_y);
    // more right --->
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        glfwSetWindowPos(window, current_x + 5, current_y);
}





