#version 330 core

layout (location = 0) in vec3 aPos;


uniform float scale; // set from GENERATE_VAO class
uniform mat4 model;

void main(){
   
   vec4 scaling = vec4(scale , scale , scale , 1.0);
   gl_Position = model * (scaling * vec4(aPos.x, aPos.y, aPos.z, 1.0));


};