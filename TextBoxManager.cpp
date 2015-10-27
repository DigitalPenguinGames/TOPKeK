#include "TextBoxManager.hpp"

/*TextBoxManager::TextBoxManager(){ }*/
TextBox                             TextBoxManager::_textBox;
std::map<std::string, std::string>  TextBoxManager::texts;

void TextBoxManager::load() {

    texts["default"] = "Check me out, check me out, i'm not a Sirian, i cri everi tim!";
    texts["penguins"] = "Penguin penguin penguin niugnep There are believed to be 17 species of penguins.  This includes the Aptendytes (Great penguins), Pygoscelis (Brush-Tailed penguins), Eudyptula (Little penguins), Megadyptes (Only 1 kind of Megadypte penguin survives), and Eudyptes (Crested penguins) Nobody really knows the root of the word penguin. The word has no English, French, Spanish or other romantic language roots. As there are no penguins in the Northern Hemisphere, it wasn’t until European explorers discovered them in the South that the world first appeared. It’s first referenced in English and Dutch as pen gwyn which in Welsh means white head.Through evolution, the penguin’s wings have evolved into flippers which are more adapted to aquatic life. Most penguins can move at a total speed of up to 6 to 12 km/h (3.7 to 7.5 mph) while underwater, but the fastest penguin (The Gentoo Penguin) can achieve a remarkable top speeds of 36 Km/h (22 mph). Emperor penguins have also been known to dive as deep as 565 meters (1,870 feet) for 22 minutes – an absolutely incredible feat for a diving bird. Most penguins species however only stay underwater for around 4-5 minutes at a time, as most of their food can be gathered from very low depths.";
    _textBox.setTexture(Resources::talkBox);
    _textBox.setTextColor(sf::Color::Black);
    _textBox.setFont(Resources::pauseMenuFont);

}

void TextBoxManager::setSize(float sizeX, float sizeY){
    _textBox.setSize(sizeX, sizeY);
}

void TextBoxManager::processEvent(sf::Event event){
    _textBox.handleEvent(event);
}

void TextBoxManager::drawText(sf::RenderTarget *window, std::string name){
    _textBox.setText(texts[name]);
    _textBox.draw(*window);
}

void TextBoxManager::drawText(sf::RenderTarget *window, std::string name,
                                 float posX, float posY){
    //textBox.draw(window);
    _textBox.setText(texts[name]);
    _textBox.setPosition(posX, posY);
    _textBox.draw(*window);
}

sf::Vector2f TextBoxManager::getSize(){
    return _textBox.getSize();
}
/*
 * void TextBoxManager::drawText(sf::RenderWindow window, std::string name,
                                 float posX, float posY, float sizeX, float sizeY){
    //textBox.draw(window);
    _textBox.setSize();
    _textBox.setText(texts[name]);
    _textBox.setPosition(posX, posY);
    _textBox.draw(window);
}*/



