#include "ClickEventCanceller.h"

void ClickEventCanceller::change_position(double x, double y) {
    posx = x;
    posy = y;
}
ClickEventCanceller::ClickEventCanceller(Shader* _shader, WINDOW* _windowobj, const char* path, double _posx, double _posy, double _scale) {
    shader = _shader;
    windowobj = _windowobj;
    posx = _posx;
    posy = _posy;
    scale = _scale;
    TEXTURE temp = TEXTURE(std::string(path));
    ID = temp.ID;

}

void ClickEventCanceller::create_canceller(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO,
    double posx, double posy, double scale) {

    texture_shader->use();
    //rendering object1
    texture_shader->transform(windowobj->window, posx, posy, scale, "block"); // 200 -xpos , 100 -ypos , 0.2 -scale;
    glBindTexture(GL_TEXTURE0 , ID);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    VAO->use();
    DRAW(6); // draw 6 vertices
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    


}
void ClickEventCanceller::render() {
    create_canceller(shader, windowobj, &VAO, posx, posy, scale);
}
