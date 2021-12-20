




// including glad used for shaders etc to configure them
#include <glad/glad.h>
// iostream idk for strings maybe or "cout"
#include <iostream>
// glfw for context which openGL need to draw in like a canvas
#include <GLFW/glfw3.h>
//type conversion
#include <string>
//source code of vertex shader yeah kinda simple
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


// fragment shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.5f, 0.2f, 1.0f);\n"
"}\n\0";



//input procces prototype
void processinput(GLFWwindow* window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{   // init glfw so we can use its things XD
    if (!glfwInit())
        return -1;

    // window size
    int windowSizeW = 640, windowSizeH = 480;
    
    
    // making the window transparent (similar to   glfwSetWindowOpacity(window, 0.5f)  ...);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    // here some stuff i dont understand xd but i think it sets the aspect ratio and monitor stuff
    int count, windowWidth, windowHeight, monitorX, monitorY;

    // I am assuming that main monitor is in the 0 position
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);
    // width: 75% of the screen
    windowWidth = static_cast<int>(videoMode->width / 1.5);
    // aspect ratio 16 to 9
    windowHeight = static_cast<int>(videoMode->height / 16 * 9);

    glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);

    // set the visibility window hint to false for subsequent window creation
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    


    /*  HERE IT SHOULD BE IN ORDER !!! 1. make window
                                        2. make the window current context
                                        3. load GLAD !*/
    // create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(windowSizeW, windowSizeH, "Hello World", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }
    // when window is clicked what it shoudl do
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // make the window's context current
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // reset the window hints to default
    glfwDefaultWindowHints();
    // here we set the window pos on screen and because we divide the monitor resolution by 2 we get the middle coordinates
    glfwSetWindowPos(window,
        monitorX + (videoMode->width - windowWidth) / 2,
        monitorY + (videoMode->height - windowHeight) / 2);

    // show the window
    glfwShowWindow(window);

    // uncomment following line to see the border of window
    // this hides the title bar and those 3 buttons and the border of the window
    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);



    /* here we load the shaders and buffers*/
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);// creating
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);// getting its source code
    glCompileShader(vertexShader);// compiling
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader // same repeats
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }



    // link shaders // HERE WE LINK THE 2 SHADERS IN A PROGRAM
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors of the program
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);// we can delete cause we have em in a program
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // render
        processinput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need
        //to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // swap front and back buffers
        glfwSwapBuffers(window);

        // poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
void processinput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    int current_x, current_y;
    glfwGetWindowPos(window, &current_x, &current_y);




    // independent keys
    // move up ^
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glfwSetWindowPos(window, current_x, current_y - 10);
    // move down v
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        glfwSetWindowPos(window, current_x, current_y + 10);
    // <--- move left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        glfwSetWindowPos(window, current_x - 10, current_y);
    // more right --->
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        glfwSetWindowPos(window, current_x + 10, current_y);
}
/*GLOBAL VARIABLES FOR MOUSE_BUTTON_CALLBACK*/
double _1xpos, _1ypos;// pos on 1st click
double _2xpos, _2ypos;// pos on 2nd click
double xoffset, yoffset;// how much should the window move on X and Y AXIS
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    
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
    
    
    

        
}
