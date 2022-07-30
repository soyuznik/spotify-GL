#version 330 core

out vec4 FragColor;
in vec2 TextureCoords;
in float glPosX;
// texture sampler
uniform sampler2D texture1;
uniform float comparePosX;
uniform bool should_be_green;


void main()
{  
       vec4 color = texture(texture1 , TextureCoords);
       if(comparePosX > glPosX){
            if(should_be_green){
               color = vec4(0.0f , 1.0f , 0.0f , 1.0f);
            }
            else{
               color = vec4(1.0f , 1.0f , 1.0f , 1.0f);
            }
       }
       FragColor = color;
}
