#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <map>
#include <iostream>
#include <SFML/Audio.hpp>

//#define SOUND static sf::Sound

class SoundManager {

public:
    static void load();

    static void playSound(std::string name);
    static void playMusic(std::string name);
    static void stopMusic(std::string name);
    static void pauseMusic(std::string name);
    static void setLoop(bool loop, std::string name);
    static void setPitch(float pitch, std::string name);
    static void setVolume(float volume, std::string name);
    static void setPosition(float x, float y, float z, std::string name);
    static void setGlobalSoundVolumen(float volume);
    static void setGlobalMusicVolumen(float volume);

private:

     static sf::Music   menuMusic;
     static sf::Music   overWorldMusic;

     static sf::SoundBuffer     attackBuf;
     static sf::SoundBuffer     softSword;
     static sf::SoundBuffer     stabSword;
     static sf::SoundBuffer     stepGround;
     static sf::SoundBuffer     linkAttack0;
     static sf::SoundBuffer     linkAttack1;
     static sf::SoundBuffer     linkAttack2;
     static sf::SoundBuffer     linkAttack3;
     static sf::SoundBuffer     shootBigBall;

     static std::map<std::string, sf::Sound> soundMap;
     static std::map<std::string, sf::Music> musicMap;
     static std::map<std::string, sf::Sound>::iterator sit;
     static std::map<std::string, sf::Music>::iterator mit;

};

#endif // SOUNDMANAGER_HPP


/*

  it = mymap.find('b');
  if (it != mymap.end())
    mymap.erase (it);

  // print content:
  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';
  std::cout << "d => " << mymap.find('d')->second << '\n';
*/
