#include "SoLoud/soloud.h"
#include "SoLoud/soloud_wav.h"
#include "SoLoud/soloud_speech.h"
#include "SoLoud/soloud_openmpt.h"
#include "SoLoud/soloud_thread.h"
#include <thread>
#include <iostream>




#include "Slider.h"

using namespace std;

class LoadAudio {
	SoLoud::Soloud* soloud = new SoLoud::Soloud(); // Engine core
	SoLoud::Wav* wav = new SoLoud::Wav();       // One sample source

	bool mmplaysound = false;
	int times_button_clicked = 0;
	int sound_handle = -1;
	double current_time = 0;
	double true_current_time = 0;
	bool seek_change = false;
	string previous;

public:
	LoadAudio();
	void Play(string path);
	void ___play_sound(string path, SoLoud::Soloud* soloud, SoLoud::Wav* wav, bool loop);
	void skip(double time);
	void back(double time);
	void pause();
	void setLooping(bool instance);
	void sync_Slider(Slider* slider);
	double time();
	double song_time();


};