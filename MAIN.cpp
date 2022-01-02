


#include "CONFIG_GL.h"
#include "SHADER.h"
#include "VAO.h"
#include "TEXTURE.h"
using namespace std;
//input procces prototype
void processinput(GLFWwindow* window);



int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{

    GLFWwindow* window = CONFIG_GL(TRANSPARENT_WINDOW_STATIC).window; // W = 640, H = 480;
    Shader shader("shaders/texture_vertex.glsl", "shaders/texture_frag.glsl");
    VertexArrayObject VAO = VertexArrayObject("vertices/triangle.buf");
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
        shader.scale(1.0);
        shader.move(window, 0, 0);
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



float distance(float x1, float y1, float x2, float y2)
{
    return(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

float calc_area(float a, float b, float c)
{
    float S;

    S = (a + b + c) / 2.0;

    return(sqrt(S * (S - a) * (S - b) * (S - c)));
}

int position(float area, float A, float B, float C)
{
    float res = area - (A + B + C);

    if (res < 0)
    {
        res *= -1;
    }

    if (res == 0 || res < 0.001)
    {
        return(1);
    }
    else
    {
        return(0);
    }
}

void calc(float x1, float y1, float x2, float y2, float x3, float y3,
    float x, float y, int* flag, float* area)
{
    float A, B, C, a, b, c, d, e, f;

    a = distance(x1, y1, x2, y2);
    b = distance(x2, y2, x3, y3);
    c = distance(x3, y3, x1, y1);
    *area = calc_area(a, b, c);

    d = distance(x1, y1, x, y);
    e = distance(x2, y2, x, y);
    f = distance(x3, y3, x, y);

    A = calc_area(d, a, e);
    B = calc_area(e, b, f);
    C = calc_area(f, c, d);

    *flag = position(*area, A, B, C);
}

bool isInTriangle(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 point) {
    int   flag = 0;
    float area = 0;

    calc(A.x, A.y, B.x, B.y, C.x, C.y, point.x, point.y, &flag, &area);
      
    if (flag) return true;
    else  return false;
}


void processinput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    int current_x, current_y;
    glfwGetWindowPos(window, &current_x, &current_y);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // vectors from triangle.buf file
        glm::vec3 A = glm::vec3(-0.5, -0.5, 0.0);// here we make
        glm::vec3 B = glm::vec3(0.5, -0.5, 0.0);//
        glm::vec3 C = glm::vec3(0.0, 0.5, 0.0);//

        


        // <function>


        int width, height;
        glfwGetWindowSize(window, &width, &height);
        //window pos
        int winx, winy;
        glfwGetWindowPos(window, &winx, &winy);
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        ypos = static_cast<double>(height) - ypos;// here we inverse the y axis  from down positive to up positive axis...
        float ndc_x = xpos / width * 2 - 1;// normalizing coordinates
        float ndc_y = ypos / height * 2 - 1;

        glm::vec3 point = glm::vec3(ndc_x ,ndc_y, 1.0f);

        std::cout << "is in triangle?! -- > " + std::to_string(isInTriangle(A,B,C,point)) << std::endl << std::endl;
        /*if (isInTriangle(w1, w2)) {
            std::cout << "TRUE\n";
        }*/

    }




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





