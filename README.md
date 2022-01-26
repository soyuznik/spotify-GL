# TRANSPARENT-TRIANGLE
a transparent backround triangle project that is slowly becoming a Graphical User Interface Engine
{ in this project im trying to make a GUI library that is based just on GLFW and OpenGL ... and other minor utility like GLM...)
(can be used in an already existent GLFW window)

Small Docummentation:
- WINDOW.h/WINDOW.cpp contains everything window related , like creating OpenGL context , and input management
- Shader.h/Shader.cpp contains everything related to shaders (usage : just created a shader object with vs/fg shaders)
- Button.h/Button.cpp contains everything related to rendering a button , input being managed by WINDOW , input based on slots 
{ create a void WINDOW::SLOTS(int slot){} to manage slots which are specified in Button constructor}
- ListObject.h/ListObject.cpp contains a list which you can add items to using listobj.add_item("<item_name>")
- ClickEventCanceller.h/.cpp is a rectagle shaped object that can block click events (has wire frame mode on)
- VAO/TEXTURE/TEXT do what they should do lol
- Panel.h/.cpp is just a rectangle that can have a custom texture (is supposed to be a uneditable textfield)

