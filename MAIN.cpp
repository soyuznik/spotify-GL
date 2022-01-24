  

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
#include "ClickEventCanceller.h"



//using namespace std because we use the C++ Standard Library headers
using namespace std;
//defining a macro for easier drawing and understanding
#define DRAW(n) glDrawArrays(GL_TRIANGLES, 0, n);


//here we define a list object variable *** needs to be changed once the list class is implemented
double y_list_offset = 0;
double y_list_offset1 = 0;
double y_list_offset2 = 0;
double list_sensitiv = 6;




void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{ //only yoffset changes\\ - when down ; + when up
    std::cout << "scrolled  "+ to_string(yoffset) << std::endl;
    y_list_offset = yoffset;
    y_list_offset1 = yoffset;
    y_list_offset2 = yoffset;
}

// the main function , code is executed here
int main()
{
    // creating a transparent static window with width 1000 and height 640
    WINDOW windowobj(TRANSPARENT_WINDOW_STATIC , 1000 , 640); 
    //creating a shader program that uses texture shaders
    Shader texture_shader("shaders/texture_vertex.glsl", "shaders/texture_frag.glsl");
    Shader color_shader("shaders/color_vertex.glsl", "shaders/color_frag.glsl");




   
    windowobj.reserve_slots(2);
    Button button = Button(&texture_shader, &windowobj, 560, 330, 0.2, 0, "vertices/square_wider.buf");
    Button button1 = Button(&texture_shader, &windowobj, 560, 380, 0.2, 1 , "vertices/square_wider.buf");
    
    ClickEventCanceller canceller = ClickEventCanceller(&texture_shader, &windowobj, "textures/container.jpg" , 560, 380, 0.21);
   
    Text antonio_bold = Text(windowobj, "fonts/Antonio-Bold.ttf");


    //<class.NORMALIZE_VALUES()> is used to transform values from 0-255 for colors to values that opengl understand , works for coordinates too (pixels)
    bool normalize = texture_shader.NORMALIZE_VALUES();


    // *** to turn wireframe mode on.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //creating a vector with objects that need to do something when clicked
    std::vector<std::vector<glm::vec3>> VAOs_that_need_input_slots;
    VAOs_that_need_input_slots.push_back(button.VAO->vec4_vector);
    VAOs_that_need_input_slots.push_back(button1.VAO->vec4_vector);
    //<VAO.return_data> is used to merge VAO's vectors into 1 (data)
    std::vector<glm::vec3> data = button.VAO->return_data(VAOs_that_need_input_slots);
    //outlayer
    std::vector<std::vector<glm::vec3>> VAOs_that_need_to_block_clicks;
    VAOs_that_need_to_block_clicks.push_back(canceller.VAO.vec4_vector);
    std::vector<glm::vec3> data_for_blocking = button.VAO->return_data(VAOs_that_need_to_block_clicks);
    // Loop until the user closes the window

    glfwSetScrollCallback(windowobj.window, scroll_callback);

    while (!glfwWindowShouldClose(windowobj.window))
    {
        glClear(GL_COLOR_BUFFER_BIT); // clearing so the moving doesnt make it leave a trace behind
        texture_shader.model_.clear();
        //texture_shader.model__.clear();



        button.change_position(button.posx, button.posy + (y_list_offset * list_sensitiv)); y_list_offset = 0;
        button1.change_position(button1.posx, button1.posy + (y_list_offset1 * list_sensitiv)); y_list_offset1 = 0;
        
        
       

       
        button.render();
        button1.render();

        button.setText(&antonio_bold, "Button1", 0.4f);
        button1.setText(&antonio_bold, "Button2", 0.4f);
        canceller.render();// panel last cause outlayer
        
        //panel.setText(&antonio_bold, "Panel", 0.4f);

        

       //process input (also button input)
        windowobj.processinput(data , data_for_blocking ,texture_shader);
        // swap front and back buffers
        glfwSwapBuffers(windowobj.window);

        // poll for and process events
        glfwPollEvents();
        
    }
    //destroy glfw object
    glfwTerminate();
    return 0;
}



