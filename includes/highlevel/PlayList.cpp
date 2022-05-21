#include "PlayList.h"
#include <algorithm>


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
    std::pair<bool , int> where_ = findInVector(list->ButtonTexts, current);
    if (where_.first == false) {
        std::cout << "PlayList.cpp >> Couldnt find current element\n";
        return;
    }
    else {
        std::string path = "data/" + list->ButtonTexts[where_.second + 1];
        current = path;
        audio->Play(path);
        pause->b->set_texture("textures/pause.png");
        pause->play_texture = false;
    }
}
void PlayList::play_previous() {

}