#version 330 core

out vec4 FragColor;
in vec2 TextureCoords;

// texture sampler
uniform sampler2D texture1;
//texture_shader.setVec4("RGBA", 0, 0, 0, 1.0); // black
//uniform vec4 RGBA; --> color()
uniform bool changeColor;

void main()
{      vec4 black = vec4(0, 0, 0, 1.0);
       if(changeColor){
       FragColor = mix(texture(texture1 , TextureCoords) , black , 0.5f);
       }
       else{
       FragColor = texture(texture1 , TextureCoords);
       }
   
}
