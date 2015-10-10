#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <map>
#include <iostream>
#include<SFML/Audio.hpp>

//#define SOUND static sf::Sound

class SoundManager {

public:
    static void load();

    static void playSound(std::string name);


private:

     static sf::Sound  attack;
     static sf::SoundBuffer attackBuf;


     static std::map<std::string, sf::Sound> soundMap;
     static std::map<std::string, sf::Sound>::iterator it;

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
