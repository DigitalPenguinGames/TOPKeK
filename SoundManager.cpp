#include "SoundManager.hpp"

//f. dec.
sf::Music           SoundManager::menuMusic;
sf::SoundBuffer     SoundManager::attackBuf;


std::map<std::string, sf::Sound> SoundManager::soundMap;
std::map<std::string, sf::Music> SoundManager::musicMap;
std::map<std::string, sf::Sound>::iterator SoundManager::sit;
std::map<std::string, sf::Music>::iterator SoundManager::mit;


void SoundManager::load(){

    if(!attackBuf.loadFromFile("Resources/Sounds/attack.ogg")){ std::cout << "Fail on loading attack" << std::endl;};
    soundMap["attack"].setBuffer(attackBuf);

    musicMap["menuMusic"].openFromFile("Resources/Sounds/menuMusic.ogg");

}



void SoundManager::playSound(std::string name){
    sit = soundMap.find(name);
    if (sit != soundMap.end()) (soundMap.find(name)->second).play();
}

void SoundManager::playMusic(std::string name){
mit = musicMap.find(name);
if (mit != musicMap.end()) (musicMap.find(name)->second).play();

}

void SoundManager::stopMusic(std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (musicMap.find(name)->second).stop();

}

void SoundManager::pauseMusic(std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (musicMap.find(name)->second).pause();

}

void SoundManager::setLoop(bool loop, std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (musicMap.find(name)->second).setLoop(loop);

}

void SoundManager::setPitch(float pitch, std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (musicMap.find(name)->second).setPitch(pitch);
}

void SoundManager::setVolume(float volume, std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (musicMap.find(name)->second).setVolume(volume);
}

void SoundManager::setPosition(float x, float y, float z, std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (musicMap.find(name)->second).setPosition(x,y,z);
}
