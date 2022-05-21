#include "PlayList.h"
#include <algorithm>

double last = __ctime();
template < typename T>
std::pair<bool, int > findInVector(const std::vector<T>& vecOfElements, const T& element)
{
    std::pair<bool, int > result;
    // Find given element in vector
    auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
    if (it != vecOfElements.end())
    {
        result.second = distance(vecOfElements.begin(), it);
        result.first = true;
    }
    else
    {
        result.first = false;
        result.second = -1;
    }
    return result;
}


PlayList::PlayList(ListObject* list_ , LoadAudio* audio_ , __Pause* pause_){
	list = list_;
    audio = audio_;
    pause = pause_;
}
void PlayList::play_next() {
    if ((__ctime() - last) < 1.5) return;
    last = __ctime();
    int position;
    std::pair<bool, int> where_ = findInVector(list->ButtonTexts, current);
    position = (where_.second) + 1;
    if (position < 0) {
        position = (list->ButtonTexts.size() - 1);
    }
    if (position > (list->ButtonTexts.size() - 1)) {
        position = 0;
    }
    if (where_.first == false) {
        std::cout << "PlayList.cpp >> Couldnt find current element\n";
        return;
    }
    else {
        current = list->ButtonTexts[position];
        std::string path = "data/" + current;
        audio->Play(path);
        pause->b->set_texture("textures/pause.png");
        pause->play_texture = false;
    }
}
void PlayList::play_previous() {
    if ((__ctime() - last) < 1.5) return;
    last = __ctime();
    int position;
    std::pair<bool, int> where_ = findInVector(list->ButtonTexts, current);
    position = (where_.second) - 1;
    if (position < 0) {
        position = (list->ButtonTexts.size() - 1);
    }
    if (position > (list->ButtonTexts.size() - 1)) {
        position = 0;
    }
    if (where_.first == false) {
        std::cout << "PlayList.cpp >> Couldnt find current element\n";
        return;
    }
    else {
        current = list->ButtonTexts[position];
        std::string path = "data/" + current;
        audio->Play(path);
        pause->b->set_texture("textures/pause.png");
        pause->play_texture = false;
    }
}