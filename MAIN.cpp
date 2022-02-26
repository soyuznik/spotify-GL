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
bool mmplaysound = false;
int times_button_clicked = 0;
int sound_handle = -1;
double current_time = 0;
double true_current_time = 0;
bool seek_change = false;
string previous;
void play_sound(std::string path , SoLoud::Soloud* soloud , SoLoud::Wav* wav , bool loop) {
	// Declare some variables
	// Load background sample
	if (previous == path) { goto play; }
	else previous = path;
	wav->load(path.c_str());       // Load a wave file
	wav->setLooping(loop);        // Tell SoLoud to loop the sound

    sound_handle = soloud->play(*wav);   
	//soloud.seek(handle1, 10);
		// Play it
	// Configure sound source
	// Wait for voice to finish
play:
	while (mmplaysound)
	{
		//true_current_time = soloud->getStreamPosition(sound_handle);
		if (seek_change) {
			soloud->seek(sound_handle, current_time);
			seek_change = false;
		}
		else current_time = soloud->getStreamPosition(sound_handle);
		// Still going, sleep for a bit
		SoLoud::Thread::sleep(10);
	}
	soloud->deinit();
	//delete soloud;
	//delete wav;
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

	SoLoud::Soloud* soloud = new SoLoud::Soloud(); // Engine core
	SoLoud::Wav* wav = new SoLoud::Wav();       // One sample source
	

	while (!glfwWindowShouldClose(windowobj.window))
	{
		glClear(GL_COLOR_BUFFER_BIT); // clearing so the moving doesnt make it leave a trace behind
		list_backround.render();
		Button* buttonnr = list.render_and_manage_input();
		if (buttonnr != NULL) {
			mmplaysound = false; times_button_clicked = 1;
			if (times_button_clicked == 1 && !mmplaysound) {
				mmplaysound = true;
				string path = "data/" + buttonnr->obj_ident;
				soloud->init();
				std::thread thr = std::thread(play_sound, path , soloud , wav , true);
				thr.detach();
				times_button_clicked++;
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
		texture_shader->setBool("is_toggled", true);
		rloop.render();
		texture_shader->setBool("is_toggled", false);
		rrandom.render();
		download.render();
		texture_shader->setBool("transparentMode", false);
		slider.render();
		menu.render();
		
		if (glfwGetMouseButton(windowobj.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			if (pause.is_clicked()) mmplaysound = false; times_button_clicked = 1;
			if (skback.is_clicked()) {
				seek_change = true;
				current_time = current_time - 5;
				if (current_time < 0) {
					current_time = 0;
				}
			}
			if (skforwar.is_clicked()) {
				seek_change = true;
				current_time = current_time + 5;
				if (current_time > wav->getLength()) {
					current_time = 0;
				}
			}
			rloop.is_clicked();
			rrandom.is_clicked();
			download.is_clicked();
			if (slider.accept_input(return_ndc_cursor(windowobj.window))) {
				seek_change = true;
				current_time = slider.return_pos(wav->getLength());
			}

			
	
		
		}
		slider.set_pos(current_time, wav->getLength());
		glfwSwapBuffers(windowobj.window);
		
		// poll for and process events
		glfwPollEvents();
	}
	//destroy glfw object
	glfwTerminate();
	return 0;
}