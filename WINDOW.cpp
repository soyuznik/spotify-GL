#include "WINDOW.h"

//for slots
#include <shellapi.h>

//used for the type of the window input *deprecated*
int INSTANT_MOUSE_CALLBACK;

//prototype that is defined later in the file
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);



//WINDOW constructor , <transparency> is a macro (see WINDOW.h)
WINDOW::WINDOW(int transparency, int width, int height) {
    // init glfw so we can use its things XD
    if (!glfwInit()) {
        std::cout << "FAILED TO LOAD GLFW\n";
        return;
    }
    windowSizeW = width;
    windowSizeH = height;
    this->DEFINE_WINDOW(transparency);

}
// used to config monitor for aspect ratio
void WINDOW::CONFIG_MONITOR() {
    // I am assuming that main monitor is in the 0 position
    monitors = glfwGetMonitors(&count);
    videoMode = glfwGetVideoMode(monitors[0]);
    // width: 75% of the screen
    windowWidth = static_cast<int>(videoMode->width / 1.5);
    // aspect ratio 16 to 9
    windowHeight = static_cast<int>(videoMode->height / 16 * 9);

    glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);
}
// will create a glfw window with the specified type (transparency)
GLFWwindow* WINDOW::DEFINE_WINDOW(int transparency) {
    this->CONFIG_MONITOR();
    bool hide_titlebar; // used for the type of the window specification
    switch (transparency) {
    case TRANSPARENT_WINDOW:
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // makes window transparent
        hide_titlebar = true; // hides titlebar when starting
        INSTANT_MOUSE_CALLBACK = 1; // sets input type response
        break;
    case TRANSPARENT_INSTANT:
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // makes window transparent
        hide_titlebar = true;
        INSTANT_MOUSE_CALLBACK = 0;
        break;
    case OPAQUE:
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE); // makes window opaque
        hide_titlebar = false; // will show title bar
        INSTANT_MOUSE_CALLBACK = 2;
        break;
    case TRANSPARENT_WINDOW_STATIC: // will make window transparent with  a titlebar
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        hide_titlebar = false;
        INSTANT_MOUSE_CALLBACK = 3;
        break;
    default: //  in case of an invalid type will print valid types and throw a exception
        std::cout << "ERROR: CONFIG_GL::DEFINE_WINDOW::transparency\n"
            << "#define TRANSPARENT_INSTANT 0\n"
            << "#define TRANSPARENT_WINDOW 1\n"
            << "#define TRANSPARENT_WINDOW_STATIC 3\n"
            << "#define TRANSPARENT_NO 2\n";
        throw(GLFW_NO_WINDOW_CONTEXT);
    }


    /*  HERE IT SHOULD BE IN ORDER !!! 1. make window
                                    2. make the window current context
                                    3. load GLAD !*/
                                    // create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(windowSizeW, windowSizeH, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cout << "FAILED TO LOAD WINDOW";
        return NULL;
    }

    // when window is clicked what it shoudl do
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // make the window's context current
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }

    // reset the window hints to default
    glfwDefaultWindowHints();
    // here we set the window pos on screen and because we divide the monitor resolution by 2 we get the middle coordinates
    glfwSetWindowPos(window,
        monitorX + (videoMode->width - windowWidth) / 2,
        monitorY + (videoMode->height - windowHeight) / 2);

    // show the window
    glfwShowWindow(window);

    // here we hide the titlebar based on the previous type
    if (hide_titlebar) {
        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    }
    else {
        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
    }


    return window; // returning GLFWwindow * window
}
/*
<distance> <calc_area> <position> < calc > <IsInTriangle>
 -- are used for input proccesing

 -- use IsInTriangle to check for where is a point


*/
// calculate distance beetween (x1,y1) ----- (x2,y2)
float distance(float x1, float y1, float x2, float y2)
{
    return(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}
// calculates the surface of a triangle with points a b c
float calc_area(float a, float b, float c)
{
    float S;

    S = (a + b + c) / 2.0;

    return(sqrt(S * (S - a) * (S - b) * (S - c)));
}
// modulus
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
//calculates if a point (x,y) is in the triangle A(x1,y1) B(x2,y2) , C(x3,y3)
void calc(float x1, float y1, float x2, float y2
    , float x3, float y3, float x, float y, int* flag, float* area) {
    /*
    * https://www.youtube.com/watch?v=ntjM9YZP0qk
    *
    * the link for the whole IsInTriangle() function explanation



    */
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
// C++ implementation of C function calc()
bool isInTriangle(glm::vec4 A, glm::vec4 B, glm::vec4 C, glm::vec4 point) {
    int   flag = 0;
    float area = 0;

    calc(A.x, A.y, B.x, B.y, C.x, C.y, point.x, point.y, &flag, &area);

    if (flag) return true;
    else  return false;
}

//the method that procceses all user input
void WINDOW::processinput(std::vector<glm::vec3> data , Shader shader) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // quit with ESC
        glfwSetWindowShouldClose(window, true);


    int current_x, current_y; // saing current window position
    glfwGetWindowPos(window, &current_x, &current_y);


    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // <function>

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        //window pos
        int winx, winy;
        glfwGetWindowPos(window, &winx, &winy);
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        ypos = static_cast<double>(height) - ypos;// here we inverse the y axis  from down positive to up positive axis...
        float ndc_x = xpos / width * 2 - 1;// normalizing coordinates x , y
        float ndc_y = ypos / height * 2 - 1;

        glm::vec4 point = glm::vec4(ndc_x, ndc_y, 1.0f, 1.0f);// creating point on screen with normalized coords
       
        //checking if square or triangle input procces

        for (unsigned int i = 0; i < ((int)data.size() / 3); i++) {
           
            // getting the vector with matrices from the shader
            std::vector<glm::mat4> model = shader.model_;
           

            // this gets corresponding vertices from data[]  and multiplying with a matrix

            // we do <[std::round(i / 2)]> because we need to get the model for the square if it was for triangle , we would do just <[i]>

            // so we get the current square position on screen , which has 2 triangles , so it will loop over all triangle in squares and checking for input
            glm::vec4 A = model[std::round(i / 2)] * glm::vec4(data[0 + (i * 3)], 1.0f);
            glm::vec4 B = model[std::round(i / 2)] * glm::vec4(data[1 + (i * 3)], 1.0f);
            glm::vec4 C = model[std::round(i / 2)] * glm::vec4(data[2 + (i * 3)], 1.0f);

            // checks where the cursor clicked and gives the triangle number , which corrensponds to <i>
           
            if(isInTriangle(A, B, C, point)) {

                //button slots
                switch (i) {
                case 0: case 1: darken_color = true; break;
                case 2: case 3: darken_color = true;;break;
                }
                break;
            }// if(isInTriangle(A, B, C, point)) 

        }
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
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    static bool is_decorated = false;
    switch (INSTANT_MOUSE_CALLBACK) { // different mouse callback -> can be edited using the global macro
    case 0:
        static double _1xpos, _1ypos;// pos on 1st click
        static double _2xpos, _2ypos;// pos on 2nd click
        static double xoffset, yoffset;// how much should the window move on X and Y AXIS
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            glfwGetCursorPos(window, &_1xpos, &_1ypos); // setting 1st click pos 

        }

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
            glfwGetCursorPos(window, &_2xpos, &_2ypos); // setting 2nd click pos


            // pool window move event
            xoffset = _2xpos - _1xpos; // offset (XY)
            yoffset = _2ypos - _1ypos;
            int currentx, currenty;
            glfwGetWindowPos(window, &currentx, &currenty);//window pos before updating
            glfwSetWindowPos(window, currentx + xoffset, currenty + yoffset);// setting new window position
        }
        break;

    case 1:

        if (is_decorated == false && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            glfwHideWindow(window);// hiding and showing to prevent weird visual bug
            glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE); // setting the decorated atribute so it shows the title bar
            glfwShowWindow(window);
            is_decorated = true;
        }
        else if (is_decorated == true && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            glfwHideWindow(window);
            glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);// setting the decorated atribute so it doesnt show the title bar
            glfwShowWindow(window);
            is_decorated = false;
        }
        break;
    case 2:
        break;

    }
}