#include "SoundManager.hpp"

//f. dec.
sf::Music           SoundManager::menuMusic;
sf::Music           SoundManager::overWorldMusic;

sf::SoundBuffer     SoundManager::attackBuf;
sf::SoundBuffer     SoundManager::softSword;
sf::SoundBuffer     SoundManager::stabSword;
sf::SoundBuffer     SoundManager::stepGround;
sf::SoundBuffer     SoundManager::linkAttack0;
sf::SoundBuffer     SoundManager::linkAttack1;
sf::SoundBuffer     SoundManager::linkAttack2;
sf::SoundBuffer     SoundManager::linkAttack3;
sf::SoundBuffer     SoundManager::shootBigBall;
//sf::SoundBuffer     SoundManager::SOUND_NAME;


std::map<std::string, sf::Sound> SoundManager::soundMap;
std::map<std::string, sf::Music> SoundManager::musicMap;
std::map<std::string, sf::Sound>::iterator SoundManager::sit;
std::map<std::string, sf::Music>::iterator SoundManager::mit;


void SoundManager::load(){

    musicMap["menuMusic"].openFromFile("Resources/Sounds/menuMusic.ogg");
    musicMap["overWorld"].openFromFile("Resources/Sounds/overWorld.ogg");

    if(!attackBuf.loadFromFile("Resources/Sounds/attack.ogg")){ std::cout << "Fail on loading attack" << std::endl;};
    soundMap["chamaleonTongue"].setBuffer(attackBuf);

    if(!softSword.loadFromFile("Resources/Sounds/espasaSuau.ogg")){ std::cout << "Fail on loading softSword" << std::endl;};
    soundMap["softSword"].setBuffer(softSword);
    if(!stabSword.loadFromFile("Resources/Sounds/espasaSeca.ogg")){ std::cout << "Fail on loading stabSword" << std::endl;};
    soundMap["stabSword"].setBuffer(stabSword);

    if(!stepGround.loadFromFile("Resources/Sounds/passaTerra.ogg")){ std::cout << "Fail on loading stepGround" << std::endl;};
    soundMap["stepGround"].setBuffer(stepGround);

    if(!linkAttack0.loadFromFile("Resources/Sounds/linkAttack0.ogg")){ std::cout << "Fail on loading linkAttack0" << std::endl;};
    soundMap["linkAttack0"].setBuffer(linkAttack0);
    if(!linkAttack1.loadFromFile("Resources/Sounds/linkAttack1.ogg")){ std::cout << "Fail on loading linkAttack1" << std::endl;};
    soundMap["linkAttack1"].setBuffer(linkAttack1);
    if(!linkAttack2.loadFromFile("Resources/Sounds/linkAttack2.ogg")){ std::cout << "Fail on loading linkAttack2" << std::endl;};
    soundMap["linkAttack2"].setBuffer(linkAttack2);
    if(!linkAttack3.loadFromFile("Resources/Sounds/linkAttack3.ogg")){ std::cout << "Fail on loading linkAttack3" << std::endl;};
    soundMap["linkAttack3"].setBuffer(linkAttack3);


    if(!shootBigBall.loadFromFile("Resources/Sounds/escupGran1.ogg")){ std::cout << "Fail on loading ShootBigBall" << std::endl;};
    soundMap["shootBigBall"].setBuffer(shootBigBall);

}



void SoundManager::playSound(std::string name){
    sit = soundMap.find(name);
    if (sit != soundMap.end()) (sit->second).play();
}

void SoundManager::playMusic(std::string name){
mit = musicMap.find(name);
if (mit != musicMap.end()) (mit->second).play();

}

void SoundManager::stopMusic(std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (mit->second).stop();

}

void SoundManager::pauseMusic(std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (mit->second).pause();

}

void SoundManager::setLoop(bool loop, std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (mit->second).setLoop(loop);

}

void SoundManager::setPitch(float pitch, std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (mit->second).setPitch(pitch);
}

void SoundManager::setVolume(float volume, std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (mit->second).setVolume(volume);
}

void SoundManager::setPosition(float x, float y, float z, std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (mit->second).setPosition(x,y,z);
}


void SoundManager::setGlobalSoundVolumen(float volume) {
    for (auto it = soundMap.begin(); it != soundMap.end(); ++it) (it->second).setVolume(volume);
}

void SoundManager::setGlobalMusicVolumen(float volume) {
    for (auto it = musicMap.begin(); it != musicMap.end(); ++it) (it->second).setVolume(volume);
}
