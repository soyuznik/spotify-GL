// higher level class
#include "highlevel/Button.h"
#include "highlevel/Panel.h"
#include "highlevel/ClickEventCanceller.h"
#include "highlevel/ListObject.h"
#include "highlevel/TextField.h"
#include "lowlevel/UTILITY.h"
#include "highlevel/Slider.h"


//using namespace std because we use the C++ Standard Library headers
using namespace std;
//defining a macro for easier drawing and understanding
#define DRAW(n) glDrawArrays(GL_TRIANGLES, 0, n);

//SLOTS
void WINDOW::SLOTS(int slot_nr) {
	switch (slot_nr) {
	case 0: cout << "slot0\n"; break;
	case 1: cout << "slot1\n"; break;
	case 2: cout << "slot2\n"; break;
	case 3: cout << "slot3\n"; break;
	case 4: cout << "slot4\n"; break;
	case 5: cout << "pause\n"; break;
	case 6: cout << "skback\n"; break;
	case 7: cout << "skforwar\n"; break;
	case 8: cout << "rloop\n"; break;
	case 9: cout << "rrandom\n"; break;
	case 10: cout << "download\n"; break;
	}
}

// the main function , code is executed here
int main()
{
	// creating a transparent static window with width 1000 and height 640
	WINDOW windowobj(TRANSPARENT_WINDOW_STATIC, 1000, 640);
	//creating a shader program that uses texture shaders
	Shader* texture_shader = new Shader("shaders/texture_vertex.glsl", "shaders/texture_frag.glsl");
	//Shader color_shader("shaders/color_vertex.glsl", "shaders/color_frag.glsl");
	//Shader discard_shader("shaders/texture_vertex.glsl", "shaders/texture_frag.glsl");
	TextField text(texture_shader, &windowobj, 400, 600);
	Panel media_bar(texture_shader, &windowobj, "textures/blacker_gray.png", 300, 0, 0.8f);
	Panel upper_bar(texture_shader, &windowobj, "textures/blacker_gray.png", 300, 600, 0.8f);
	ListObject list = ListObject(texture_shader, &windowobj, 663, 650, 0.2);
	double t = 1.2;

	Panel list_backround = Panel(texture_shader, &windowobj,
		"textures/gray.png", 600, 400, 0.8f , "vertices/square_extra_high.buf");
	Button rrandom = Button(texture_shader, &windowobj, 300 * t, 90, 0.1f, 9);
	Button skback = Button(texture_shader, &windowobj, 355 * t, 90, 0.1f, 6);
	Button pause = Button(texture_shader, &windowobj, 410 * t, 90, 0.1f, 5);
	Button skforwar = Button(texture_shader, &windowobj, 465 * t, 90, 0.1f, 7);
	Button rloop = Button(texture_shader, &windowobj, 520 * t, 90, 0.1f, 8);
	Button download = Button(texture_shader, &windowobj, 250, 610, 0.1f, 10);
	Panel menu = Panel(texture_shader, &windowobj, "textures/menu.jpg", 0, 350, 0.5f, "vertices/square_little_higher_menu.buf");
	//texture seetting
	rrandom.set_texture("textures/random.jpg");
	skback.set_texture("textures/skback.jpg");
	pause.set_texture("textures/pause.jpg");
	skforwar.set_texture("textures/skforwar.jpg");
	rloop.set_texture("textures/loop.jpg");
	download.set_texture("textures/download.png");



	Slider slider = Slider(texture_shader, &windowobj, "textures/gray.png", 490, 50, 0.1f);

	list.add_item("Button0");
	list.add_item("Button1");
	list.add_item("Button2");
	list.add_item("Button3");
	list.add_item("Button4");

	//<class.NORMALIZE_VALUES()> is used to transform values from 0-255 for colors to values that opengl understand , works for coordinates too (pixels)
	bool normalize = texture_shader->NORMALIZE_VALUES();

	

	while (!glfwWindowShouldClose(windowobj.window))
	{
		glClear(GL_COLOR_BUFFER_BIT); // clearing so the moving doesnt make it leave a trace behind
		list_backround.render();
		list.render();
		list.manage_scroll();
		upper_bar.render();
		media_bar.render();
		text.logkey();
		text.render();
		text.check_input();
		//glfwSwapInterval(0);
		texture_shader->use();
		texture_shader->setBool("transparentMode", true);
		pause.render();
		skback.render();
		skforwar.render();
		rloop.render();
		rrandom.render();
		download.render();
		texture_shader->setBool("transparentMode", false);


		slider.render();
		menu.render();
		if (glfwGetMouseButton(windowobj.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			pause.accept_input(return_ndc_cursor(windowobj.window), 5);
			skback.accept_input(return_ndc_cursor(windowobj.window), 6);
			skforwar.accept_input(return_ndc_cursor(windowobj.window), 7);
			rloop.accept_input(return_ndc_cursor(windowobj.window), 8);
			rrandom.accept_input(return_ndc_cursor(windowobj.window), 9);
			download.accept_input(return_ndc_cursor(windowobj.window), 10);
			slider.accept_input(return_ndc_cursor(windowobj.window));
			
	
		
		}
		glfwSwapBuffers(windowobj.window);
		
		// poll for and process events
		glfwPollEvents();
	}
	//destroy glfw object
	glfwTerminate();
	return 0;
}