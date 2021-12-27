


#include "CONFIG_GL.h"
#include "SHADER.h"
#include "GENERATE_VAO.h"


//input procces prototype
void processinput(GLFWwindow* window);



int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
     
    GLFWwindow* window = CONFIG_GL().DEFINE_WINDOW(TRANSPARENT_WINDOW); // W = 640, H = 480;
    Shader shader("VERTEXSHADER.glsl", "FRAGMENTSHADER.glsl");
    unsigned int VAO = GENERATE_VAO("vertices/triangle.buf").return_VAO();
   
    bool normalize = shader.NORMALIZE_VALUES();
    
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // render
        
        processinput(window);

        
        shader.use();
        shader.scale(0.7);
        shader.color(6, 150, 120 , 255);
        shader.move(window , 0, 0);
        //RGB color (6, 150, 120)

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





