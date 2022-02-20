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
	Button rrandom = Button(texture_shader, &windowobj, 300 * t, 90, 0.1f);
	Button skback = Button(texture_shader, &windowobj, 355 * t, 90, 0.1f);
	Button pause = Button(texture_shader, &windowobj, 410 * t, 90, 0.1f);
	Button skforwar = Button(texture_shader, &windowobj, 465 * t, 90, 0.1f);
	Button rloop = Button(texture_shader, &windowobj, 520 * t, 90, 0.1f);
	Button download = Button(texture_shader, &windowobj, 250, 610, 0.1f);
	Panel menu = Panel(texture_shader, &windowobj, "textures/menu.jpg", 0, 350, 0.5f, "vertices/square_little_higher_menu.buf");
	//texture seetting
	rrandom.set_texture("textures/random.jpg");
	skback.set_texture("textures/skback.jpg");
	pause.set_texture("textures/pause.jpg");
	skforwar.set_texture("textures/skforwar.jpg");
	rloop.set_texture("textures/loop.jpg");
	download.set_texture("textures/download.png");



	Slider slider = Slider(texture_shader, &windowobj, "textures/gray.png", 490, 50, 0.1f);
	std::vector dir = listdir("data");
	for (int i = 0; i < dir.size(); i++) {
		Button* butt = list.add_item(dir[i]);
		butt->obj_ident =  dir[i];
	}

	//<class.NORMALIZE_VALUES()> is used to transform values from 0-255 for colors to values that opengl understand , works for coordinates too (pixels)
	bool normalize = texture_shader->NORMALIZE_VALUES();

	

	while (!glfwWindowShouldClose(windowobj.window))
	{
		glClear(GL_COLOR_BUFFER_BIT); // clearing so the moving doesnt make it leave a trace behind
		list_backround.render();
		Button* buttonnr = list.render_and_manage_input();
		if (buttonnr != NULL) {
			std::string path = string("C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\data\\" + buttonnr->obj_ident);
			ex_textfile(path);
		}
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
			pause.is_clicked();
			skback.is_clicked();
			skforwar.is_clicked();
			rloop.is_clicked();
			rrandom.is_clicked();
			download.is_clicked();
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