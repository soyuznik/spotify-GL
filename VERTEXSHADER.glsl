#version 330 core

layout (location = 0) in vec3 aPos;


uniform mat4 scale; // set from GENERATE_VAO class

void main(){
   
  
   gl_Position = scale * vec4(aPos.x, aPos.y, aPos.z, 1.0);


};