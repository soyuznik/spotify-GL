


#include "CONFIG_GL.h"
#include "SHADER.h"
#include "VAO.h"
#include "TEXTURE.h"

//input procces prototype
void processinput(GLFWwindow* window);



int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
     
    GLFWwindow* window = CONFIG_GL(TRANSPARENT_WINDOW).window; // W = 640, H = 480;
    Shader shader("shaders/texture_vertex.glsl", "shaders/texture_frag.glsl");
    VertexArrayObject VAO = VertexArrayObject("vertices/square.buf");
    TEXTURE texture = TEXTURE("textures/container.jpg");
    
    
    bool normalize = shader.NORMALIZE_VALUES();

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Loop until the user closes the window
    int random = 0;
    while (!glfwWindowShouldClose(window))
    {
        // render
        
        processinput(window);

        
        shader.use();
        shader.scale(0.7);
        shader.move(window, 140, 0);
        texture.use();
        
        VAO.use();
        
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
    //glfwGetCursorPos(window, &xpos, &ypos);
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << std::to_string(xpos) + "," + std::to_string(ypos) << std::endl;
    }
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





