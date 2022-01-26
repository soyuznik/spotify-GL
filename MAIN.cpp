
// higher level class
#include "highlevel/Button.h"
#include "highlevel/Panel.h"
#include "highlevel/ClickEventCanceller.h"
#include "highlevel/ListObject.h"


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

    Panel panel = Panel(&texture_shader, &windowobj, "textures/button.jpg", 200, 100, 0.15f);
    Text antonio_bold = Text(windowobj, "fonts/Antonio-Bold.ttf");
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

    
    std::string log;
    int logframes = 0;
    while (!glfwWindowShouldClose(windowobj.window))
    {
        glClear(GL_COLOR_BUFFER_BIT); // clearing so the moving doesnt make it leave a trace behind
        texture_shader.model_.clear();
        texture_shader.model__.clear();
        
        list.render();
        list.manage_scroll();
        std::map<std::string, int> k{
            { "A", GLFW_KEY_A},//letters
            { "B" , GLFW_KEY_B },
            { "C" , GLFW_KEY_C },
            { "D" , GLFW_KEY_D },
            { "E" , GLFW_KEY_E },
            { "F" , GLFW_KEY_F },
            { "G" , GLFW_KEY_G },
            { "H" , GLFW_KEY_H },
            { "I" , GLFW_KEY_I },
            { "J" , GLFW_KEY_J },
            { "K" , GLFW_KEY_K },
            { "L" , GLFW_KEY_L },
            { "M" , GLFW_KEY_M },
            { "N" , GLFW_KEY_N },
            { "O" , GLFW_KEY_O },
            { "P" , GLFW_KEY_P },
            { "Q" , GLFW_KEY_Q },
            { "R" , GLFW_KEY_R },
            { "S" , GLFW_KEY_S },
            { "T" , GLFW_KEY_T },
            { "U" , GLFW_KEY_U },
            { "V" , GLFW_KEY_V },
            { "W" , GLFW_KEY_W },
            { "X" , GLFW_KEY_X },
            { "Y" , GLFW_KEY_Y },
            { "Z" , GLFW_KEY_Z },//numbers
            { "0" , GLFW_KEY_0 },
            { "1" , GLFW_KEY_1 },
            { "2" , GLFW_KEY_2 },
            { "3" , GLFW_KEY_3 },
            { "4" , GLFW_KEY_4 },
            { "5" , GLFW_KEY_5 },
            { "6" , GLFW_KEY_6 },
            { "7" , GLFW_KEY_7 },
            { "8" , GLFW_KEY_8 },
            { "9" , GLFW_KEY_9 },
            { "," , GLFW_KEY_COMMA },//other
            { " " , GLFW_KEY_SPACE },
            { "/" , GLFW_KEY_SLASH },
            { "." , GLFW_KEY_PERIOD },
            { "delete" , GLFW_KEY_BACKSPACE} // delete last character
        }; // keymap
        // iterate using C++17 facilities
        if (logframes == 5) {
            for (const auto& n : k) {
                auto letter = n.first;
                auto value = n.second;
                if (glfwGetKey(windowobj.window, value) == GLFW_PRESS) {
                    if (letter == "delete") {
                        log = log.substr(0, log.size() - 1); logframes = 0;
                        break;//remove last charachter from log
                    }
                    else {
                            log.append(letter); logframes = 0; break; // add character
                        }
                    }
                }
            }
        else logframes++;
        panel.render();
        antonio_bold.drawText(log, 100, 100, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

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



