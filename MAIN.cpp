  


#include "WINDOW.h"
#include "SHADER.h"
#include "VAO.h"
#include "TEXTURE.h"
using namespace std;
//input procces prototype




int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{

    WINDOW windowobj(TRANSPARENT_WINDOW_STATIC); // W = 640, H = 480;
    Shader shader("shaders/texture_vertex.glsl", "shaders/texture_frag.glsl");
    VertexArrayObject VAO = VertexArrayObject("vertices/triangle.buf");
    TEXTURE texture = TEXTURE("textures/container.jpg");
    

    bool normalize = shader.NORMALIZE_VALUES();

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Loop until the user closes the window
    int random = 0;
    while (!glfwWindowShouldClose(windowobj.window))
    {
        // render

        


        shader.use();
        shader.transform(windowobj.window, 200, 100 , 0.2);
        windowobj.processinput(VAO.vertices_vec4 , shader);

        texture.use();
        VAO.use();

        glDrawArrays(GL_TRIANGLES, 0, 6);
        // swap front and back buffers
        glfwSwapBuffers(windowobj.window);

        // poll for and process events
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}



