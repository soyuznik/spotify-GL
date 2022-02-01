
// higher level class
#include "highlevel/Button.h"
#include "highlevel/Panel.h"
#include "highlevel/ClickEventCanceller.h"
#include "highlevel/ListObject.h"
#include "highlevel/TextField.h"


//using namespace std because we use the C++ Standard Library headers
using namespace std;
//defining a macro for easier drawing and understanding
#define DRAW(n) glDrawArrays(GL_TRIANGLES, 0, n);


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
    TextField text(&texture_shader, &windowobj, 400, 600);
    
    ListObject list = ListObject(&texture_shader, &windowobj, 832, 650, 0.2);

   
    windowobj.reserve_slots(5);
    list.add_item("Button0");
    list.add_item("Button1");
    list.add_item("Button2");
    list.add_item("Button3");
    list.add_item("Button4");
    

    //<class.NORMALIZE_VALUES()> is used to transform values from 0-255 for colors to values that opengl understand , works for coordinates too (pixels)
    bool normalize = texture_shader.NORMALIZE_VALUES();

    //<VAO.return_data> is used to merge VAO's vectors into 1 (data)
    std::vector<glm::vec3> data = list.return_clickable_data();
    std::vector<glm::vec3> data_for_blocking = list.return_blocking_data();
    // Loop until the user closes the window

    
   
    while (!glfwWindowShouldClose(windowobj.window))
    {
        glClear(GL_COLOR_BUFFER_BIT); // clearing so the moving doesnt make it leave a trace behind
      
        list.render();
        list.manage_scroll();


        text.logkey();
        text.render();
        text.check_input();
        //glfwSwapInterval(0);
        glfwSwapBuffers(windowobj.window);

        // poll for and process events
        glfwPollEvents();
        
    }
    //destroy glfw object
    glfwTerminate();
    return 0;
}



