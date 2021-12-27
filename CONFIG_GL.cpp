#include "CONFIG_GL.h"
int INSTANT_MOUSE_CALLBACK;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);



CONFIG_GL::CONFIG_GL() {
    // init glfw so we can use its things XD
    if (!glfwInit()) {
        std::cout << "FAILED TO LOAD GLFW\n";
        return;
    }

    
}
void CONFIG_GL::CONFIG_MONITOR() {
    // I am assuming that main monitor is in the 0 position
    monitors = glfwGetMonitors(&count);
    videoMode = glfwGetVideoMode(monitors[0]);
    // width: 75% of the screen
    windowWidth = static_cast<int>(videoMode->width / 1.5);
    // aspect ratio 16 to 9
    windowHeight = static_cast<int>(videoMode->height / 16 * 9);

    glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);
}
GLFWwindow* CONFIG_GL::DEFINE_WINDOW(int transparency) {
    this->CONFIG_MONITOR();
    bool hide_titlebar;
    switch (transparency) {
    case TRANSPARENT_WINDOW:
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        hide_titlebar = true;
        INSTANT_MOUSE_CALLBACK = 1;
        break;
    case TRANSPARENT_INSTANT:
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        hide_titlebar = true;
        INSTANT_MOUSE_CALLBACK = 0;
        break;
    case OPAQUE:
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
        hide_titlebar = false;
        INSTANT_MOUSE_CALLBACK = 2;
        break;
    case TRANSPARENT_WINDOW_STATIC:
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        hide_titlebar = false;
        INSTANT_MOUSE_CALLBACK = 3;
        break;
    default:
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
    if (!window){
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

    
    if (hide_titlebar) {
        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    }
    else {
        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
    }


    return window;
}


/*GLOBAL VARIABLES FOR MOUSE_BUTTON_CALLBACK*/
double _1xpos, _1ypos;// pos on 1st click
double _2xpos, _2ypos;// pos on 2nd click
double xoffset, yoffset;// how much should the window move on X and Y AXIS

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    static bool is_decorated = false;
    switch(INSTANT_MOUSE_CALLBACK) { // different mouse callback -> can be edited using the global macro
    case 0:
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