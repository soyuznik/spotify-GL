#include "MAINWIN.h"
// including glad used for shaders etc to configure them



void MAINWIN::use()
{
    glUseProgram(ID);
}
void MAINWIN::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void MAINWIN::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void MAINWIN::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void __forceinline mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
MAINWIN::MAINWIN(int w , int h) {
	windowSizeW = w;
	windowSizeH = h;
}
void MAINWIN::ConfigOpenGL() {
    
    // init glfw so we can use its things XD
    if (!glfwInit())
        return ;

   


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
    window = glfwCreateWindow(windowSizeW, windowSizeH, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return ;
    }
    // when window is clicked what it shoudl do
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // make the window's context current
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return ;
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
}
void MAINWIN::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
void MAINWIN::processinput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    int current_x, current_y;
    glfwGetWindowPos(window, &current_x, &current_y);




    // independent keys
    // move up ^
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
void MAINWIN::CreateShaderProgram(const char* vertexPath, const char* fragmentPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    GLuint vertex = NULL;
    GLuint fragment = NULL;
    // 2. compile shaders
    // vertex shader
    try {
        vertex = glCreateShader(GL_VERTEX_SHADER);
    }
    catch (...) {
        if(vertex == NULL){checkCompileErrors(vertex, "VERTEX");}
    }
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
   
    // fragment Shader
    try {
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
    }
    catch (...) {
        if(fragment == NULL){checkCompileErrors(fragment, "FRAGMENT");}
    }
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
/*GLOBAL VARIABLES FOR MOUSE_BUTTON_CALLBACK*/
double _1xpos, _1ypos;// pos on 1st click
double _2xpos, _2ypos;// pos on 2nd click
double xoffset, yoffset;// how much should the window move on X and Y AXIS
void __forceinline mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    static bool is_decorated = false;
    if (INSTANT_MOUSE_CALLBACK) { // different mouse callback -> can be edited using the global macro
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
    else {
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

    }
}
void MAINWIN::ConfigDrawing(float vertices[]) {
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
}

