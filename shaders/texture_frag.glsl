#version 330 core

out vec4 FragColor;
in vec2 TextureCoords;

// texture sampler
uniform sampler2D texture1;
//texture_shader.setVec4("RGBA", 0, 0, 0, 1.0); // black
//uniform vec4 RGBA; --> color()
uniform bool changeColor;
uniform bool transparentMode;
uniform bool is_toggled;
void main()
{      vec4 black = vec4(0, 0, 0, 1.0);
       vec4 color;
       vec4 default_color = texture(texture1 , TextureCoords);
       if(changeColor){
       color = mix(texture(texture1 , TextureCoords) , black , 0.5f);
       }
       else if(is_toggled){
       color = mix(texture(texture1 , TextureCoords) , black , 0.3f);
       }
       else{
       color = texture(texture1 , TextureCoords);
       }
       if(transparentMode){
              if(default_color.r > 0.75 && default_color.g > 0.75 && default_color.b > 0.5){
                 discard;
                 }
       }
       FragColor = color;
}
