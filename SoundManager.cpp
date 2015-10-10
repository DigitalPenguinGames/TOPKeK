#include "SoundManager.hpp"

//f. dec.
sf::Sound           SoundManager::attack;
sf::SoundBuffer     SoundManager::attackBuf;

std::map<std::string, sf::Sound>           SoundManager::soundMap;
std::map<std::string, sf::Sound>::iterator SoundManager::it;

void SoundManager::load(){

    if(!attackBuf.loadFromFile("Resources/Sounds/attack.ogg")){ std::cout << "Fail on loading attack" << std::endl;};
    attack.setBuffer(attackBuf);
    soundMap["attack"] = attack;

}

void SoundManager::playSound(std::string name){
    it = soundMap.find(name);
      if (it != soundMap.end()) (soundMap.find(name)->second).play();
}
