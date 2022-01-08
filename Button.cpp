#include "Button.h"


Button::Button(Shader* _shader, WINDOW* _windowobj , double _posx, double _posy, double _scale, int* _frames, int* _slot) {
    shader = _shader;
    windowobj = _windowobj;
    posx = _posx;
    posy = _posy;
    scale = _scale;
    frames = _frames;
    slot = _slot;
}

void Button::create_button(Shader* texture_shader, WINDOW* windowobj, VertexArrayObject* VAO, TEXTURE* texture,
    double posx, double posy, double scale, int* frames, int* slot) {

    texture_shader->use();
    if (*frames > 10) { texture_shader->setBool("changeColor", false); windowobj->slot[*slot] = false; *frames = 0; }
    else if (windowobj->slot[*slot]) {
        /*
        NOTE: for some reason changing uniform works only from mainloop and only if its directly like this
        because the uniform should be updated every frame!
        should note for future button slots implementation

        */
        texture_shader->setBool("changeColor", true);
        *frames = *frames + 1;

    }

    //rendering object1
    texture_shader->transform(windowobj->window, posx, posy, scale); // 200 -xpos , 100 -ypos , 0.2 -scale;
    texture->use(); // pick texture
    VAO->use(); // pick vao
    DRAW(6); // draw 6 vertices
    texture_shader->setBool("changeColor", false);

}
void Button::render() {
    create_button(shader, windowobj, &VAO, &texture , posx, posy, scale, frames, slot);
}