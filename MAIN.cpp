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


//using namespace std because we use the C++ Standard Library headers
using namespace std;
//defining a macro for easier drawing and understanding
#define DRAW(n) glDrawArrays(GL_TRIANGLES, 0, n);


#include <algorithm>
void download(std::string text) {
	system((std::string("c: & cd C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\dependencies & youtube-dl -o ") +
		std::string("C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\data\\out.mp4  ") + text).c_str());
	
	std::vector v = listdir("data");
	if (std::find(v.begin(), v.end(), "out.mp4") != v.end()) {
		/* v contains mp4 file */
		system(std::string("cd C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\data & ffmpeg -i out.mp4 -vn out.mp3 & del out.mp4").c_str());
	}
	if (std::find(v.begin(), v.end(), "out.mkv") != v.end()) {
		/* v contains mkv file */
		system(std::string("cd C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\data & ffmpeg -i out.mkv -vn out.mp3 & del out.mkv").c_str());
	}
	else {
		/* v does not contain any supported format */
		printf("\n Failed to download video ");
		printf(text.c_str());
		printf("\n");
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

	//LoadAudio
	LoadAudio audio = LoadAudio();

	//Shader discard_shader("shaders/texture_vertex.glsl", "shaders/texture_frag.glsl");
	
	Panel media_bar(texture_shader, &windowobj, "textures/blacker_gray.png", 300, 0, 0.8f);
	Panel upper_bar(texture_shader, &windowobj, "textures/blacker_gray.png", 300, 600, 0.8f);
	ListObject list = ListObject(texture_shader, &windowobj, 610, 650, 0.2);
	double t = 1.2;

	Panel list_backround = Panel(texture_shader, &windowobj,
		"textures/gray.png", 600, 400, 0.8f, "vertices/square_extra_high.buf");
	Button rrandom = Button(texture_shader, &windowobj, 305 * t, 80, 0.05f);
	Button skback = Button(texture_shader, &windowobj, 355 * t, 80, 0.09f);
	Button pause = Button(texture_shader, &windowobj, 410 * t, 80, 0.12f);
	Button skforwar = Button(texture_shader, &windowobj, 465 * t, 80, 0.09f);
	Button rloop = Button(texture_shader, &windowobj, 515 * t, 80, 0.059f);
	//Button download = Button(texture_shader, &windowobj, 250, 610, 0.09f);
	Panel vol_img = Panel(texture_shader, &windowobj, "textures/vol.png", 810, 40, 0.05f , "vertices/square.buf");
	Panel menu = Panel(texture_shader, &windowobj, "textures/menu.jpg", -50, 350, 0.5f, "vertices/square_little_higher_menu.buf");

	//menu buttons
	Button mitem1 = Button(texture_shader, &windowobj, 135, 551, 0.1f , "vertices/square_wider_menu.buf");
	Button mitem2 = Button(texture_shader, &windowobj, 135, 505, 0.1f, "vertices/square_wider_menu.buf");
	Button mitem3 = Button(texture_shader, &windowobj, 135, 459, 0.1f, "vertices/square_wider_menu.buf");
	Text* font = new Text(windowobj, "fonts/Antonio-Light.ttf");

	Panel SettingsBackround = Panel(texture_shader, &windowobj, "textures/gray.png", 500, 340, 2.0f, "vertices/square.buf");
	Panel DownloadsBackround = Panel(texture_shader, &windowobj, "textures/gray.png", 500, 340, 2.0f, "vertices/square.buf");
	TextField text(texture_shader, &windowobj, 420, 540);
	Button searchB = Button(texture_shader, &windowobj, 770, 540, 0.1f , "vertices/square.buf");
	searchB.set_texture("textures/download.png");
	//textures menu----
	mitem1.set_texture("textures/itemm.png");
	mitem2.set_texture("textures/itemm.png");
	mitem3.set_texture("textures/itemm.png");


	//texture seettings
	rrandom.set_texture("textures/random.png");
	skback.set_texture("textures/skback.png");
	pause.set_texture("textures/play.png");
	skforwar.set_texture("textures/skforwar.png");
	rloop.set_texture("textures/loop.png");
	//download.set_texture("textures/download.png");

	Slider slider = Slider(texture_shader, &windowobj, "textures/gray.png", 490, 40, 0.1f);
	std::vector dir = listdir("data");
	for (int i = 0; i < dir.size(); i++) {
		Button* butt = list.add_item(dir[i]);
		butt->obj_ident = dir[i];
	}
	VolSlider volslider = VolSlider(texture_shader, &windowobj, "textures/gray.png", 900, 40, 0.1f);
	
	//<class.NORMALIZE_VALUES()> is used to transform values from 0-255 for colors to values that opengl understand , works for coordinates too (pixels)
	bool normalize = texture_shader->NORMALIZE_VALUES();
	bool tmp_1 = true;
	bool play_texture = false;


	bool MainMenuLayer = true;
	bool SettingsLayer = false;
	bool DownloadsLayer = false;



	while (!glfwWindowShouldClose(windowobj.window))
	{
		glClear(GL_COLOR_BUFFER_BIT); // clearing so the moving doesnt make it leave a trace behind
		if (MainMenuLayer) {
			list_backround.render();
			Button* buttonnr = list.render_and_manage_input();
			if (buttonnr != NULL) {
				string path = "data/" + buttonnr->obj_ident;
				audio.Play(path);
				pause.set_texture("textures/pause.png");
				play_texture = false;
			}
			list.manage_scroll();
		}
		if (SettingsLayer) {
			SettingsBackround.render();
			font->drawText("Settings Menu not implemented", 350, 500, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
		}
		if (DownloadsLayer) {
			DownloadsBackround.render();
			texture_shader->setBool("transparentMode", true);
			text.render();
			text.check_input();
			text.logkey();
			searchB.render();
			texture_shader->setBool("transparentMode", false);
			if (searchB.is_clicked()) {
				std::thread downloader = std::thread(&download, text.text());
				downloader.detach();
				
			}
			//font->drawText("Downloads Menu not implemented", 350, 500, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
		}
		upper_bar.render();
		media_bar.render();
		//text.logkey();
		//text.render();
		//text.check_input();
		//glfwSwapInterval(0);
		texture_shader->use();
		texture_shader->setBool("transparentMode", true);

		pause.render();
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
		mitem3.render();
		mitem1.setTextM(font, "Main Menu", 0.6f, 1.0f, 1.0f, 1.0f);
		mitem2.setTextM(font, "Settings", 0.6f, 1.0f, 1.0f, 1.0f);
		mitem3.setTextM(font, "Downloads", 0.6f, 1.0f, 1.0f, 1.0f);


		if (glfwGetMouseButton(windowobj.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			if (mitem1.is_clicked()) {
				MainMenuLayer = true;
				SettingsLayer = false;
				DownloadsLayer = false;
				
			}
			if (mitem2.is_clicked()) {
				SettingsLayer = true;
				MainMenuLayer = false;
				DownloadsLayer = false;
			}
			if (mitem3.is_clicked()) {
				MainMenuLayer = false;
				SettingsLayer = false;
				DownloadsLayer = true;
			}


			if (pause.is_clicked() && tmp_1) {
				tmp_1 = false;
				audio.pause();
				if (play_texture) {
					play_texture = false;
					pause.set_texture("textures/pause.png");
				}
				else if (!play_texture) {
					play_texture = true;
					pause.set_texture("textures/play.png");
				}
			}
			if (skback.is_clicked()) {
				
				audio.back(5);
			}
			if (skforwar.is_clicked()) {
				
				audio.skip(5);
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
	//destroy glfw object
	glfwTerminate();
	return 0;
}