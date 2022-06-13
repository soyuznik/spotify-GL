/*
---------------------------------< BEWARE > <<SPAGHETTI CODE>>!!!!!!!!!!!!!!!!!!--------------------
                              READ AT OWN RISK -------------------------------------------------------
*/




// higher level class
#include "highlevel/Button.h"
#include "highlevel/Panel.h"
#include "highlevel/ClickEventCanceller.h"
#include "highlevel/ListObject.h"
#include "highlevel/TextField.h"
#include "lowlevel/UTILITY.h"
#include "highlevel/Slider.h"
#include "highlevel/VolSlider.h"
#include "highlevel/LoadAudio.h"
#include "highlevel/PlayList.h"
#include "highlevel/Pause.h"
#include "highlevel/VerticalSlider.h"
#include "highlevel/Checkbox.h"
//using namespace std because we use the C++ Standard Library headers
using namespace std;
//defining a macro for easier drawing and understanding
#define DRAW(n) glDrawArrays(GL_TRIANGLES, 0, n);



// the main function , code is executed here
int main()
{
	// creating a transparent static window with width 1000 and height 640
	WINDOW windowobj(TRANSPARENT_WINDOW_STATIC, 1000, 640);
	//SHADERS
	Shader* texture_shader = new Shader("Resources/shaders/texture_vertex.glsl", "Resources/shaders/texture_frag.glsl");
	Shader* slider_shader = new Shader("Resources/shaders/slider_vertex.glsl", "Resources/shaders/slider_frag.glsl");
	//LoadAudio
	LoadAudio audio = LoadAudio();
	//PANELS
	Panel media_bar(texture_shader, &windowobj, "Resources/textures/blacker_gray.png", 300, 0, 0.8f);
	Panel upper_bar(texture_shader, &windowobj, "Resources/textures/VIOLET.jpg", 300, 600, 0.8f);
	Panel vol_img = Panel(texture_shader, &windowobj, "Resources/textures/vol.png", 810, 40, 0.05f, "Resources/vertices/square.buf");
	Panel menu = Panel(texture_shader, &windowobj, "Resources/textures/menu.jpg", -50, 350, 0.5f, "Resources/vertices/square_little_higher_menu.buf");
	Panel SettingsBackround = Panel(texture_shader, &windowobj, "Resources/textures/background-gray.png", 500, 340, 2.0f, "Resources/vertices/square.buf");
	Panel DownloadsBackround = Panel(texture_shader, &windowobj, "Resources/textures/gray.png", 500, 340, 2.0f, "Resources/vertices/square.buf");
	Panel list_backround = Panel(texture_shader, &windowobj,
		"Resources/textures/background-gray.png", 600, 400, 0.8f, "Resources/vertices/square_extra_high.buf");
	Panel upperIcon = Panel(texture_shader, &windowobj, "Resources/textures/opengl_logo.png", 135, 590, 0.1f, "Resources/vertices/square_wider_logo.buf");


	// BUTTONS
	Button rrandom = Button(texture_shader, &windowobj, 366, 80, 0.05f);
	Button skback = Button(texture_shader, &windowobj, 426, 80, 0.09f);
	Button skforwar = Button(texture_shader, &windowobj, 558, 80, 0.09f);
	Button rloop = Button(texture_shader, &windowobj, 618, 80, 0.059f);

	Button mitem1 = Button(texture_shader, &windowobj, 135, 491, 0.1f, "Resources/vertices/square_wider_menu.buf");
	Button mitem2 = Button(texture_shader, &windowobj, 135, 445, 0.1f, "Resources/vertices/square_wider_menu.buf");
	Button searchB = Button(texture_shader, &windowobj, 770, 540, 0.1f, "Resources/vertices/square.buf");

	// Checkbox
	Checkbox* check = new Checkbox(texture_shader, &windowobj, 310, 540, 0.05f);
	// LIST
	ListObject list = ListObject(texture_shader, &windowobj, 610, 650, 0.2);
	// Sliders
	Slider slider = Slider(slider_shader, &windowobj, "Resources/textures/gray.png", 490, 40, 0.1f);
	std::vector dir = listdir("Resources/data");
	for (int i = 0; i < dir.size(); i++) {
		ListButton* butt = list.add_item(dir[i]);
		butt->obj_ident = dir[i];
	}
	VolSlider volslider = VolSlider(slider_shader, &windowobj, "Resources/textures/gray.png", 900, 40, 0.1f);
	VerticalSlider scroller = VerticalSlider(texture_shader, &windowobj, "Resources/textures/gray.png", 990, 350, 0.1f);

	// Text-related
	Text* font = new Text(windowobj, "Resources/fonts/OpenSans-Bold.ttf");
	//TextField text(texture_shader, &windowobj, 420, 540);
	// __PAUSE custom button
	__Pause pause = __Pause(texture_shader, &windowobj, 492, 80, 0.12f);
	// playlist
	PlayList playlist(&list, &audio, &pause);

	// settings
	check->indent("HIDE_VERTICAL_SLIDER");
	searchB.set_texture("Resources/textures/download.png");
	mitem1.set_texture("Resources/textures/itemm.png");
	mitem2.set_texture("Resources/textures/itemm.png");
	rrandom.set_texture("Resources/textures/random.png");
	skback.set_texture("Resources/textures/skback.png");
	pause.b->set_texture("Resources/textures/play.png");
	skforwar.set_texture("Resources/textures/skforwar.png");
	rloop.set_texture("Resources/textures/loop.png");
	check->set_active("Resources/textures/checkbox_active.png");
	check->set_unactive("Resources/textures/checkbox_unactive.png");
	texture_shader->NORMALIZE_VALUES();
	slider_shader->NORMALIZE_VALUES();
	bool tmp_1 = true;



	bool MainMenuLayer = true;
	bool SettingsLayer = false;
	bool DownloadsLayer = false;
	bool HIDE_VERTICAL_SLIDER;

	//getting logged settings
	ifstream reader("Resources/settings.cfg");
	std::string line;
	while (getline(reader, line)) {
		size_t where_two_dots;
		// HIDE_VERTICAL_SLIDER check
		if (line.find(check->obj_ident) != std::string::npos) {
			where_two_dots = line.find(":");
			std::string data = line.substr(where_two_dots + 1, 10);
			if (stoi(data) == 0) check->set_activebool(false);
			if (stoi(data) == 1) check->set_activebool(true);
		}
	}
	reader.close();
	while (!glfwWindowShouldClose(windowobj.window))
	{
		glClear(GL_COLOR_BUFFER_BIT); // clearing so the moving doesnt make it leave a trace behind


		HIDE_VERTICAL_SLIDER = check->is_active();
		//check->set_activebool(HIDE_VERTICAL_SLIDER);
		

		if (MainMenuLayer) {
			list_backround.render();
			ListButton* buttonnr = list.render_and_manage_input();
			if (buttonnr != NULL) {
				string path = "Resources/data/" + buttonnr->obj_ident;
				playlist.current = buttonnr->obj_ident;
				audio.Play(path);
				pause.b->set_texture("Resources/textures/pause.png");
				pause.play_texture = false;
			}
			list.manage_scroll();
			if (!HIDE_VERTICAL_SLIDER) {
				scroller.render();
			}
			if (!HIDE_VERTICAL_SLIDER) {
				if (scroller.accept_input(return_ndc_cursor(windowobj.window))) {
					std::cout << "Slider activated!\n";
				}
			}

		}
		if (SettingsLayer) {
			SettingsBackround.render();
			check->render();
			check->is_clicked();
			//Checkbox* check = new Checkbox(texture_shader, &windowobj, 310, 540, 0.05f);
			font->drawText("Hide vertical scrollbar", 330, 534, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		
		
		
		//if (DownloadsLayer) {
			//DownloadsBackround.render();
			//texture_shader->setBool("transparentMode", true);
			//text.render();
			//text.check_input();
			//text.logkey();
			//searchB.render();
			//texture_shader->setBool("transparentMode", false);
			//if (searchB.is_clicked()) {
			//	InitDownload(text.text());

			//}
			//font->drawText("Downloads Menu not implemented", 350, 500, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

		upper_bar.render();
		media_bar.render();
		//text.logkey();
		//text.render();
		//text.check_input();
		//glfwSwapInterval(0);
		texture_shader->use();
		texture_shader->setBool("transparentMode", true);

		pause.b->render();
		skback.render();
		skforwar.render();
		//texture_shader->setBool("is_toggled", true);
		rloop.render();
		//texture_shader->setBool("is_toggled", false);
		rrandom.render();
		//download.render();
		texture_shader->setBool("transparentMode", false);
		slider.render();
		volslider.render();
		
		vol_img.render();

		//menu rendering
		menu.render();
		mitem1.render();
		mitem2.render();
		//mitem3.render();
		mitem1.setTextM(font, "Main Menu", 0.6f, 1.0f, 1.0f, 1.0f);
		mitem2.setTextM(font, "Settings", 0.6f, 1.0f, 1.0f, 1.0f);
		//mitem3.setTextM(font, "Downloads", 0.6f, 1.0f, 1.0f, 1.0f);
		
		texture_shader->setBool("transparentMode", true);
		upperIcon.render();
		texture_shader->setBool("transparentMode", false);


		// process HOVER EVENTS
		if (slider.accept_hover_input(return_ndc_cursor(windowobj.window))) {
			slider.SHOW_DOT = true;
		}
		else slider.SHOW_DOT = false;
		
		if (volslider.accept_hover_input(return_ndc_cursor(windowobj.window))) {
			volslider.SHOW_DOT = true;
		}
		else volslider.SHOW_DOT = false;


		
		if (glfwGetMouseButton(windowobj.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			if (mitem1.is_clicked()) {
				MainMenuLayer = true;
				SettingsLayer = false;
				DownloadsLayer = false;

			};
			if (mitem2.is_clicked()) {
				SettingsLayer = true;
				MainMenuLayer = false;
				DownloadsLayer = false;
			};
			//if (mitem3.is_clicked()) {
			//	MainMenuLayer = false;
			//	SettingsLayer = false;
			//	DownloadsLayer = true;
			//}


			if (pause.b->is_clicked() && tmp_1) {
				tmp_1 = false;
				audio.pause();
				if (pause.play_texture) {
					pause.play_texture = false;
					pause.b->set_texture("Resources/textures/pause.png");
				}
				else if (!pause.play_texture) {
					pause.play_texture = true;
					pause.b->set_texture("Resources/textures/play.png");
				}
			}
			if (skback.is_clicked()) {
				
				audio.back(&playlist);
			}
			if (skforwar.is_clicked()) {
				
				audio.skip(&playlist);
			}
			rloop.is_clicked();
			rrandom.is_clicked();
			//download.is_clicked();
			if (slider.accept_input(return_ndc_cursor(windowobj.window))) {
				audio.sync_Slider(&slider);
			}
			if (volslider.accept_input(return_ndc_cursor(windowobj.window))) {
				volslider.set_volume(&audio);
			}
			

		}
		slider.set_pos(audio.time(), audio.song_time());
		glfwSwapBuffers(windowobj.window);
		//final input proccesing
		if (glfwGetMouseButton(windowobj.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			tmp_1 = true;
		}
		// poll for and process events
		glfwPollEvents();
		
	}


	ofstream writer("Resources/settings.cfg");
	writer << check->obj_ident << " : " << (int)check->is_active() << "\n";
	writer.close();
	//destroy glfw object
	glfwTerminate();
	return 0;
}