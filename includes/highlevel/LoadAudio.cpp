// main header
#include "LoadAudio.h"



// setVolume method (double volume) argument
void LoadAudio::setVolume(float vol__) {
	vol = vol__;
	UPDATE_SOUND = true;
}

// empty constructor
LoadAudio::LoadAudio() { soloud->init(); }

// playsound instance
void LoadAudio::___play_sound(std::string path, SoLoud::Soloud* soloud, SoLoud::Wav* wav, bool loop) {

	// Declare some variables
	// Load background sample
	
	if (previous == path) { goto play; }
	else previous = path;
	wav->load(path.c_str());
	wav->setLooping(loop);        // Tell SoLoud to loop the sound
	sound_handle = soloud->play(*wav , vol); // play <wav> file
	// Wait for voice to finish
play:
	while (mmplaysound)
	{
		soloud->setVolume(sound_handle, vol);
		//true_current_time = soloud->getStreamPosition(sound_handle);
		if (seek_change) {
			soloud->seek(sound_handle, current_time);
			seek_change = false;
		}
		else current_time = soloud->getStreamPosition(sound_handle);
		// Still going, sleep for a bit
		SoLoud::Thread::sleep(10);
	}
	
}
// returns sample len
double LoadAudio::song_time() {
	return this->wav->getLength();
}
// returns current time
double LoadAudio::time() {
	return this->current_time;
}

// sync
void LoadAudio::sync_Slider(Slider* slider) {
	seek_change = true;
	current_time = slider->return_pos(wav->getLength());
}

// back <time> time
void LoadAudio::back(double time) {
	seek_change = true;
	current_time = current_time - time;
	if (current_time < 0) {
		current_time = 0;
	}
}
// skip <time> time
void LoadAudio::skip(double time) {
	seek_change = true;
	current_time = current_time + time;
	if (current_time > wav->getLength()) {
		current_time = 0;
	}
}
// pause / play
void LoadAudio::pause() {
	if (button___ins == 0) { soloud->setPauseAll(true); button___ins = 1; }
	else if (button___ins == 1) { soloud->setPauseAll(false);  button___ins = 0; }
}
// __play_sound thread invoker
void LoadAudio::Play(string path) {
	//if (difftime((TIME), start) > 2) {
	//	start = TIME;
	    if ((__ctime() - last) < 0.5) return;
	    last = __ctime();
		mmplaysound = true; // start thread with playing
		thread thr = thread(&LoadAudio::___play_sound, this, path, soloud, wav, true);
		thr.detach(); // detach
//	}
}