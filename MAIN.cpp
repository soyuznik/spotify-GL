  

//WINDOW header that  we use to  create window / add utility
#include "WINDOW.h"
//SHADER header that we use to draw on the screen and  start a shader program
#include "SHADER.h"
//VAO header that we use to store data that is sent to GPU and other utility
#include "VAO.h"
//TEXTURE header that we use to add textures to primitives.
#include "TEXTURE.h"
//TEXT header that  we use to render text
#include "TEXT.h"



// higher level class
#include "Button.h"
#include "Panel.h"




//using namespace std because we use the C++ Standard Library headers
using namespace std;
//defining a macro for easier drawing and understanding
#define DRAW(n) glDrawArrays(GL_TRIANGLES, 0, n);



// the main function , code is executed here
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
    // creating a transparent static window with width 1000 and height 640
    WINDOW windowobj(TRANSPARENT_WINDOW_STATIC , 1000 , 640); 
    //creating a shader program that uses texture shaders
    Shader texture_shader("shaders/texture_vertex.glsl", "shaders/texture_frag.glsl");



    //Time management
    int frames = 0;
    int frames1 = 0;

    //2 slots
    int slot0 = 0;
    int slot1 = 1;
    windowobj.reserve_slots(2);
    Button button = Button(&texture_shader, &windowobj, 410, 380, 0.2, &frames, &slot0);
    Button button1 = Button(&texture_shader, &windowobj, 560, 380, 0.2, &frames1, &slot1);
    Panel panel = Panel(&texture_shader, &windowobj, "textures/marble.jpg" , 700, 380, 0.2);
   
    Text antonio_bold = Text(windowobj, "fonts/Antonio-Bold.ttf");


    //<class.NORMALIZE_VALUES()> is used to transform values from 0-255 for colors to values that opengl understand , works for coordinates too (pixels)
    bool normalize = texture_shader.NORMALIZE_VALUES();


    // *** to turn wireframe mode on.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //creating a vector with objects that need to do something when clicked
    std::vector<std::vector<glm::vec3>> VAOs_that_need_input_slots;
    VAOs_that_need_input_slots.push_back(button.VAO.vec4_vector);
    VAOs_that_need_input_slots.push_back(button1.VAO.vec4_vector);
    //<VAO.return_data> is used to merge VAO's vectors into 1 (data)
    std::vector<glm::vec3> data = button.VAO.return_data(VAOs_that_need_input_slots);
    // Loop until the user closes the window

    

    while (!glfwWindowShouldClose(windowobj.window))
    {
        
        button.render();
        button1.render();
        panel.render();



        button.setText(&antonio_bold, "Button1" , 0.4f, 0.0f, 0.0f, 0.0f);
        button1.setText(&antonio_bold, "Button2", 0.4f, 0.0f, 0.0f, 0.0f);
        panel.setText(&antonio_bold, "Panel", 0.4f, 0.0f, 0.0f, 0.0f);

        

       //process input (also button input)
        windowobj.processinput(data , texture_shader);
        // swap front and back buffers
        glfwSwapBuffers(windowobj.window);

        // poll for and process events
        glfwPollEvents();
        
    }
    //destroy glfw object
    glfwTerminate();
    return 0;
}



