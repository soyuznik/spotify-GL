#version 330 core

out vec4 FragColor;
in vec2 TextureCoords;
in float glPosX;
// texture sampler
uniform sampler2D texture1;
uniform float comparePosX;



void main()
{  
       vec4 color = texture(texture1 , TextureCoords);
       if(comparePosX > glPosX){
            color = vec4(0.0f , 1.0f , 0.0f , 1.0f);
       }
       FragColor = color;
}
