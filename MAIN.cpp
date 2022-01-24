  

//WINDOW header that  we use to  create window / add utility
#include "lowlevel/WINDOW.h"
//SHADER header that we use to draw on the screen and  start a shader program
#include "lowlevel/SHADER.h"
//VAO header that we use to store data that is sent to GPU and other utility
#include "lowlevel/VAO.h"
//TEXTURE header that we use to add textures to primitives.
#include "lowlevel/TEXTURE.h"
//TEXT header that  we use to render text
#include "lowlevel/TEXT.h"



// higher level class
#include "highlevel/Button.h"
#include "highlevel/Panel.h"
#include "highlevel/ClickEventCanceller.h"
#include "highlevel/ListObject.h"


//using namespace std because we use the C++ Standard Library headers
using namespace std;
//defining a macro for easier drawing and understanding
#define DRAW(n) glDrawArrays(GL_TRIANGLES, 0, n);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{ //only yoffset changes\\ - when down ; + when up
    
    WINDOW* windowobj_ = static_cast<WINDOW*>(glfwGetWindowUserPointer(window));
    windowobj_->update_list_scroll(yoffset);
    
}
//SLOTS
void WINDOW::SLOTS(int slot_nr){
    switch (slot_nr) {
    case 0: cout << "slot0\n"; break;
    case 1: cout << "slot1\n"; break;
    case 2: cout << "slot2\n"; break;
    case 3: cout << "slot3\n"; break;
    case 4: cout << "slot4\n"; break;

    } 
}
// the main function , code is executed here
int main()
{
    // creating a transparent static window with width 1000 and height 640
    WINDOW windowobj(TRANSPARENT_WINDOW_STATIC , 1000 , 640); 
    //creating a shader program that uses texture shaders
    Shader texture_shader("shaders/texture_vertex.glsl", "shaders/texture_frag.glsl");
    Shader color_shader("shaders/color_vertex.glsl", "shaders/color_frag.glsl");


    glfwSetWindowUserPointer(windowobj.window, &windowobj);
    ListObject list = ListObject(&texture_shader, &windowobj, 832, 650, 0.2);
    windowobj.reserve_slots(5);
    list.add_item("Button1");
    list.add_item("Button2");
    list.add_item("Button3");
    list.add_item("Button4");
    list.add_item("Button5");

    
    


    //<class.NORMALIZE_VALUES()> is used to transform values from 0-255 for colors to values that opengl understand , works for coordinates too (pixels)
    bool normalize = texture_shader.NORMALIZE_VALUES();


    // *** to turn wireframe mode on.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
  
   
    //<VAO.return_data> is used to merge VAO's vectors into 1 (data)
    std::vector<glm::vec3> data = list.return_clickable_data();
    std::vector<glm::vec3> data_for_blocking = list.return_blocking_data();
    // Loop until the user closes the window

    glfwSetScrollCallback(windowobj.window, scroll_callback);

    while (!glfwWindowShouldClose(windowobj.window))
    {
        glClear(GL_COLOR_BUFFER_BIT); // clearing so the moving doesnt make it leave a trace behind
        texture_shader.model_.clear();
        texture_shader.model__.clear();
        list.manage_scroll();
        list.render();

       //process input (also button input)
        windowobj.processinput(data , data_for_blocking , texture_shader);
        // swap front and back buffers
        glfwSwapBuffers(windowobj.window);

        // poll for and process events
        glfwPollEvents();
        
    }
    //destroy glfw object
    glfwTerminate();
    return 0;
}



