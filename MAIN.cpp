  


#include "WINDOW.h"
#include "SHADER.h"
#include "VAO.h"
#include "TEXTURE.h"
#include "TEXT.h"
using namespace std;

#define DRAW(n) glDrawArrays(GL_TRIANGLES, 0, n);





int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{

    WINDOW windowobj(TRANSPARENT_WINDOW_STATIC , 1000 , 640); // W = 640, H = 480;
    Shader texture_shader("shaders/texture_vertex.glsl", "shaders/texture_frag.glsl");
    VertexArrayObject VAO = VertexArrayObject("vertices/square.buf");
    TEXTURE texture = TEXTURE("textures/container.jpg");
    Text antonio_bold = Text(windowobj, "fonts/Antonio-Bold.ttf");

    bool normalize = texture_shader.NORMALIZE_VALUES();

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Loop until the user closes the window
    
    while (!glfwWindowShouldClose(windowobj.window))
    {
        // render
        //rendering triangle 
        texture_shader.use();
        texture_shader.transform(windowobj.window, 200, 100 , 0.2);
        texture.use();
        VAO.use();

        DRAW(6);

        //drawing  text
        antonio_bold.drawText("********", 0, 10, 2, glm::vec3(0.0f, 0.0f, 1.0f));
       
        
        

       //process input (also button input)
        windowobj.processinput(VAO.vec4_vector , texture_shader);
        // swap front and back buffers
        glfwSwapBuffers(windowobj.window);

        // poll for and process events
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}



