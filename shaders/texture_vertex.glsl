#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoords;


uniform float scale; // set from GENERATE_VAO class
uniform mat4 model;


out vec2 TextureCoords;
void main(){
   
   
   gl_Position = model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   TextureCoords = aTextureCoords;


};