// higher level class
#include "highlevel/Button.h"
#include "highlevel/Panel.h"
#include "highlevel/ClickEventCanceller.h"
#include "highlevel/ListObject.h"
#include "highlevel/TextField.h"
#include "lowlevel/UTILITY.h"
#include "highlevel/Slider.h"
#include "SoLoud/soloud.h"
#include "SoLoud/soloud_wav.h"
#include "SoLoud/soloud_speech.h"
#include "SoLoud/soloud_openmpt.h"
#include "SoLoud/soloud_thread.h"
#include <thread>
//using namespace std because we use the C++ Standard Library headers
using namespace std;
//defining a macro for easier drawing and understanding
#define DRAW(n) glDrawArrays(GL_TRIANGLES, 0, n);

//SLOTSs

void play_sound(std::string path) {
	// Declare some variables
	SoLoud::Soloud soloud; // Engine core
	SoLoud::Wav wav;       // One sample source


	// Initialize SoLoud (automatic back-end selection)
	// also, enable visualization for FFT calc
	soloud.init();
	soloud.setVisualizationEnable(1);


	// Load background sample
	wav.load(path.c_str());       // Load a wave file
	wav.setLooping(1);                          // Tell SoLoud to loop the sound
	int handle1 = soloud.play(wav);   
	//soloud.seek(handle1, 10);
		// Play it
	// Configure sound source
	// Wait for voice to finish
	while (true)
	{
		// Still going, sleep for a bit
		SoLoud::Thread::sleep(100);
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
	Button rrandom = Button(texture_shader, &windowobj, 305 * t, 80, 0.05f);
	Button skback = Button(texture_shader, &windowobj, 355 * t, 80, 0.09f);
	Button pause = Button(texture_shader, &windowobj, 410 * t, 80, 0.12f);
	Button skforwar = Button(texture_shader, &windowobj, 465 * t, 80, 0.09f);
	Button rloop = Button(texture_shader, &windowobj, 515 * t, 80, 0.05f);
	Button download = Button(texture_shader, &windowobj, 250, 610, 0.1f);
	Panel menu = Panel(texture_shader, &windowobj, "textures/menu.jpg", 0, 350, 0.5f, "vertices/square_little_higher_menu.buf");
	//texture seetting
	rrandom.set_texture("textures/random.jpg");
	skback.set_texture("textures/skback.jpg");
	pause.set_texture("textures/pause.jpg");
	skforwar.set_texture("textures/skforwar.jpg");
	rloop.set_texture("textures/loop.jpg");
	download.set_texture("textures/download.jpg");



	Slider slider = Slider(texture_shader, &windowobj, "textures/gray.png", 490, 40, 0.1f);
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
		static int i = 1;
		if (buttonnr != NULL) {
			if (i == 1) {
				string path = "data/" + buttonnr->obj_ident;
				std::thread thr = std::thread(play_sound, path);
				thr.detach();
				i++;
			}

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