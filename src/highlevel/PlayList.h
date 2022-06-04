#include "ListObject.h"
#include "Pause.h"
#include "LoadAudio.h"
class PlayList{
public:
	ListObject* list;
	LoadAudio* audio;
	__Pause* pause;
	std::string current;
	PlayList(ListObject* list_, LoadAudio* audio_, __Pause* pause_);
	void play_next();
	void play_previous();
};