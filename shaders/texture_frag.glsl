#version 330 core

out vec4 FragColor;
in vec2 TextureCoords;

// texture sampler
uniform sampler2D texture1;
uniform vec4 RGBA;
uniform bool changeColor;

void main()
{
   
       FragColor = RGBA;
   
}
