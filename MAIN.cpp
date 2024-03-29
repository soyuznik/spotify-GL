﻿// higher level class
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
#include "highlevel/Downloader.h"


//using namespace std because we use the C++ Standard Library headers
using namespace std;
//defining a macro for easier drawing and understanding
#define DRAW(n) glDrawArrays(GL_TRIANGLES, 0, n);





// the main function , code is executed here
int main()
{
	// Hide Console for the moment
	HideConsole();
	// creating a transparent static window with width 1000 and height 640
	WINDOW windowobj(TRANSPARENT_WINDOW_STATIC, 1000, 640);
	//creating a shader program that uses texture shaders
	Shader* texture_shader = new Shader("Resources/shaders/texture_vertex.glsl", "Resources/shaders/texture_frag.glsl");
	Shader* slider_shader = new Shader("Resources/shaders/slider_vertex.glsl", "Resources/shaders/slider_frag.glsl");

	//LoadAudio
	LoadAudio audio = LoadAudio();

	//ListObject
	ListObject list = ListObject(texture_shader, &windowobj, 610, 650, 0.2);

	//Buttons
	Button rrandom = Button(texture_shader, &windowobj, 366, 80, 0.05f);
	Button skback = Button(texture_shader, &windowobj, 426, 80, 0.09f);
	__Pause pause = __Pause(texture_shader, &windowobj, 492, 80, 0.12f);
	Button skforwar = Button(texture_shader, &windowobj, 558, 80, 0.09f);
	Button rloop = Button(texture_shader, &windowobj, 618, 80, 0.059f);
	Button mitem1 = Button(texture_shader, &windowobj, 135, 491, 0.1f, "Resources/vertices/square_wider_menu.buf");
	Button mitem2 = Button(texture_shader, &windowobj, 135, 444, 0.1f, "Resources/vertices/square_wider_menu.buf");
	Button mitem3 = Button(texture_shader, &windowobj, 135, 397, 0.1f, "Resources/vertices/square_wider_menu.buf");
	Button searchB = Button(texture_shader, &windowobj, 770, 540, 0.1f, "Resources/vertices/square.buf");
	Button Download = Button(texture_shader, &windowobj, 950, 540, 0.14f, "Resources/vertices/square.buf");
	
	//Checkbox
	Checkbox* check = new Checkbox(texture_shader, &windowobj, 310, 540, 0.05f);
	Checkbox* check1 = new Checkbox(texture_shader, &windowobj, 310, 500, 0.05f);

	//Panels
	Panel upperIcon = Panel(texture_shader, &windowobj, "Resources/textures/opengl_logo.png", 100, 590, 0.1f, "Resources/vertices/square_wider_logo.buf");
	Panel houseIcon = Panel(texture_shader, &windowobj, "Resources/textures/house.jpg", 38, 488, 0.09f, "Resources/vertices/square.buf");
	Panel gearIcon = Panel(texture_shader, &windowobj, "Resources/textures/gear.png", 38, 443, 0.1f, "Resources/vertices/square.buf");
	Panel downIcon = Panel(texture_shader, &windowobj, "Resources/textures/download_ic.png", 38, 395, 0.08f, "Resources/vertices/square.buf");
	Panel media_bar(texture_shader, &windowobj, "Resources/textures/blacker_gray.png", 300, 0, 0.8f);
	Panel upper_bar(texture_shader, &windowobj, "Resources/textures/VIOLET.jpg", 300, 600, 0.8f);
	Panel list_backround = Panel(texture_shader, &windowobj,
		"Resources/textures/background-gray.png", 600, 400, 0.8f, "Resources/vertices/square_extra_high.buf");
	Panel SettingsBackround = Panel(texture_shader, &windowobj, "Resources/textures/background-gray.png", 500, 340, 2.0f, "Resources/vertices/square.buf");
	Panel DownloadsBackround = Panel(texture_shader, &windowobj, "Resources/textures/background-gray.png", 500, 340, 2.0f, "Resources/vertices/square.buf");
	Panel vol_img = Panel(texture_shader, &windowobj, "Resources/textures/vol.png", 810, 40, 0.05f, "Resources/vertices/square.buf");
	Panel menu = Panel(texture_shader, &windowobj, "Resources/textures/menu.jpg", -50, 350, 0.5f, "Resources/vertices/square_little_higher_menu.buf");

	// Fonts
	Text* font = new Text(windowobj, "Resources/fonts/OpenSans-Bold.ttf");

	//Downloader
	Downloader downloader(font);

	//Sliders
	Slider slider = Slider(slider_shader, &windowobj, "Resources/textures/gray.png", 490, 40, 0.1f);
	std::vector dir = listdir("Resources/data");
	for (int i = 0; i < dir.size(); i++) {
		ListButton* butt = list.add_item(dir[i]);
		butt->obj_ident = dir[i];
	}
	VolSlider volslider = VolSlider(slider_shader, &windowobj, "Resources/textures/gray.png", 900, 40, 0.1f);
	VerticalSlider scroller = VerticalSlider(texture_shader, &windowobj, "Resources/textures/gray.png", 990, 350, 0.1f);

	//Playlist
	PlayList playlist(&list, &audio, &pause);

	//TextField
	TextField etext = TextField(texture_shader, &windowobj, 500, 540);


	searchB.set_texture("Resources/textures/download.png");
	mitem1.set_texture("Resources/textures/itemm.png");
	mitem2.set_texture("Resources/textures/itemm.png");
	mitem3.set_texture("Resources/textures/itemm.png");
	rrandom.set_texture("Resources/textures/random.png");
	skback.set_texture("Resources/textures/skback.png");
	pause.b->set_texture("Resources/textures/play.png");
	Download.set_texture("Resources/textures/downL.png");
	Download.should_change_color = false;
	skforwar.set_texture("Resources/textures/skforwar.png");
	rloop.set_texture("Resources/textures/loop.png");
	check->set_active("Resources/textures/checkbox_active.png");
	check->set_unactive("Resources/textures/checkbox_unactive.png");
	check->indent("HIDE_VERTICAL_SLIDER");
	check1->set_active("Resources/textures/checkbox_active.png");
	check1->set_unactive("Resources/textures/checkbox_unactive.png");
	check1->indent("HIDE_CPP_CONSOLE");
	texture_shader->NORMALIZE_VALUES();
	slider_shader->NORMALIZE_VALUES();

	bool toggle_release_1 = true;
	bool MainMenuLayer = true;
	bool SettingsLayer = false;
	bool DownloadsLayer = false;
	bool HIDE_VERTICAL_SLIDER;
	bool HIDE_CPP_CONSOLE;

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
		//HIDE_CPP_CONSOLE check1
		if (line.find(check1->obj_ident) != std::string::npos) {
			where_two_dots = line.find(":");
			std::string data = line.substr(where_two_dots + 1, 10);
			if (stoi(data) == 0) check1->set_activebool(false);
			if (stoi(data) == 1) check1->set_activebool(true);
		}
	}
	reader.close();
//////////////////////////////////// -- MAIN LOOP -- //////////////////////////////////////////////

	while (!glfwWindowShouldClose(windowobj.window))
	{
		glClear(GL_COLOR_BUFFER_BIT); // clearing so the moving doesnt make it leave a trace behind
		HIDE_VERTICAL_SLIDER = check->is_active();
		HIDE_CPP_CONSOLE = check1->is_active();
		if (HIDE_CPP_CONSOLE) HideConsole();
		else ShowConsole();


///////////////-- Choosing a Layer ---///////////////////////////////////////////////////////////////////////////////////////
		
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
			if (!HIDE_VERTICAL_SLIDER) { scroller.render(); }
			if (!HIDE_VERTICAL_SLIDER) { if (scroller.accept_input(return_ndc_cursor(windowobj.window))) { std::cout << "Slider activated!\n"; } }
		}
		if (SettingsLayer) {
			SettingsBackround.render();
			check->render();
			check->is_clicked();
			check1->render();
			check1->is_clicked();
			font->drawText("Hide vertical scrollbar", 330, 534, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
			font->drawText("Hide C++ console", 330, 490, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		if (DownloadsLayer) {
			DownloadsBackround.render();
			etext.render();
			Download.render();
		}

/////////////////////////-- Rendering objects --//////////////////////////////////////////////////////////////////////////////
//--------------------------++++++++++++++------------------//////////////////////////////////////////////////////////////////
		//RENDERING SOLID OBJECTS
		upper_bar.render();
		media_bar.render();
		texture_shader->use();
		menu.render();
		mitem1.render();
		mitem2.render();
		mitem3.render();
		slider.render();
		volslider.render();
		vol_img.render();
		//RENDERING TRANSPARENT OBJECTS
/* -- Enable transparency -- */ texture_shader->setBool("transparentMode", true); 
/*------------=======--------*/ //glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		pause.b->render();
		skback.render();
		skforwar.render();
		rloop.render();
		rrandom.render();
		upperIcon.render();
		houseIcon.render();
		gearIcon.render();
		downIcon.render();
/* -- Disable transparency -- */ texture_shader->setBool("transparentMode", false); 

		// RENDERING TEXT
		mitem1.setTextM(font, "Home", 0.5f, 0.71f, 0.71f, 0.71f);
		mitem2.setTextM(font, "Settings", 0.5f, 0.71f, 0.71f, 0.71f);
		mitem3.setTextM(font, "Downloads", 0.5f, 0.71f, 0.71f, 0.71f);

///////////////////////// PROCESS INPUT EVENTS ///////////////////////////////////////////
// 		   =-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-==--==-=-=-=--=-==-=-=-=-=-=-  /////////
		// process HOVER EVENTS
		if (slider.accept_hover_input(return_ndc_cursor(windowobj.window))) {
			slider.SHOW_DOT = true;
		}
		else slider.SHOW_DOT = false;

		if (volslider.accept_hover_input(return_ndc_cursor(windowobj.window))) {
			volslider.SHOW_DOT = true;
		}
		else volslider.SHOW_DOT = false;

		//procces general events
		if (DownloadsLayer) {
			etext.check_input();
			etext.logkey();
			if (Download.is_clicked()) {
				downloader.Download(etext.text());
			}
			downloader.render();
		}
		// Process click input (if clicked!)
		if (glfwGetMouseButton(windowobj.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			//check if any menu items were clicked!
			if (mitem1.is_clicked()) { MainMenuLayer = true; SettingsLayer = false; DownloadsLayer = false; };
			if (mitem2.is_clicked()) { SettingsLayer = true; MainMenuLayer = false; DownloadsLayer = false; };
			if (mitem3.is_clicked()) { SettingsLayer = false; MainMenuLayer = false; DownloadsLayer = true; };

			
			// Check if any buttons were clicked
			if (pause.b->is_clicked() && toggle_release_1) {
				toggle_release_1 = false; audio.pause();
				if (pause.play_texture) {
					pause.play_texture = false;
					pause.b->set_texture("Resources/textures/pause.png");
				}
				else if (!pause.play_texture) {
					pause.play_texture = true;
					pause.b->set_texture("Resources/textures/play.png");
				}
			}
			if (skback.is_clicked()) { audio.back(&playlist); }
			if (skforwar.is_clicked()) { audio.skip(&playlist); }
			rloop.is_clicked();
			rrandom.is_clicked();
			if (slider.accept_input(return_ndc_cursor(windowobj.window))) { audio.sync_Slider(&slider); }
			if (volslider.accept_input(return_ndc_cursor(windowobj.window))) { volslider.set_volume(&audio); }
		}
		slider.set_pos(audio.time(), audio.song_time());
		glfwSwapBuffers(windowobj.window);

		//final input proccesing
		if (glfwGetMouseButton(windowobj.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			toggle_release_1 = true;
		}
		
		// poll for and process events
		glfwPollEvents();
	}
//////////////// POST RUNNING EVENTS /////////////////-----///////////////////////////////////////////
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\\//\/\/\\/\/\/\/\/\/\/\//

	ofstream writer("Resources/settings.cfg");
	writer << check->obj_ident << " : " << (int)check->is_active() << "\n";
	writer << check1->obj_ident << " : " << (int)check1->is_active() << "\n";
	writer.close();
	//destroy glfw object
	glfwTerminate();
	return 0;
}