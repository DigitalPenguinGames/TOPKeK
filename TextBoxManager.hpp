#ifndef TEXTBOXMANAGER_HPP
#define TEXTBOXMANAGER_HPP

#include <map>
#include <iostream>
#include "TextBox.hpp"
#include "Resources.hpp"
#include <SFML/Graphics.hpp>

class TextBoxManager {

public:
    //TextBoxManager();
    static void load();
    static sf::Vector2f getSize();
    static void setTexture(int value);
    static void setText(std::string name);
    static void processEvent(sf::Event event);
    static void loadTexts(std::string fileName);
    static void setText(std::string name, int charSize);
    static void setSize(float sizeX, float sizeY);
    static void drawText(sf::RenderTarget *window);
    static void drawText(sf::RenderTarget *window, float posX, float posY);
    //static void drawText(sf::RenderWindow window, std::string name, float posX, float posY, float sizeX, float sizeY);
    static bool getTextFinished();

private:

    static TextBox _textBox;
    static std::map<std::string, std::string> texts;

};

#endif // TEXTBOXMANAGER_HPP

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
