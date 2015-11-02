#include "Speaker.hpp"
#include "TextBoxManager.hpp"

Speaker::Speaker(){//: Prop{
    _speaking = false;
    _text = "default";
    //llegir l'string en el descriptor (¿?)
}

bool Speaker::getSpeaking() const{
    return _speaking;
}

void Speaker::setSpeaking(bool value){
    _speaking = value;
    if(!_speaking){

        TextBoxManager::setSize(50,25);
        TextBoxManager::setText(_text, 8);

    }
}
std::string Speaker::text() const{
    return _text;
}

void Speaker::setText(const std::string &text){
    _text = text;
}


