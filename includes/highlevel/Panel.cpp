#include "Panel.h"
void Panel::change_position(double x, double y) {
    posx = x;
    posy = y;
}
Panel::Panel(Shader* _shader, WINDOW* _windowobj, const char* path, double _posx, double _posy, double _scale) {
    shader = _shader;
    windowobj = _windowobj;
    posx = _posx;
    posy = _posy;
    scale = _scale;
    TEXTURE* temp = new TEXTURE(std::string(path));
    ID = temp->ID;
   
}

void Panel::create_panel(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO,
    double posx, double posy, double scale) {
    
    texture_shader->use();
    //rendering object1
    texture_shader->transform(windowobj->window, posx, posy, scale , "none"); // 200 -xpos , 100 -ypos , 0.2 -scale;
    glBindTexture(GL_TEXTURE_2D, ID);// pick texture
    VAO->use(); // pick vao
    DRAW(6); // draw 6 vertices
    

}
void Panel::render() {
    create_panel(shader, windowobj, &VAO, posx, posy, scale);
}
void Panel::setText(Text* font, std::string text, float scale, float R, float G, float B) {
    font->drawText(text, posx - 40, posy, scale, glm::vec3(R, G, B));
}