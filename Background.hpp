#ifndef __BACKGROUND_HPP__
#define __BACKGROUND_HPP__

#include "utils.hpp"
#include "Resources.hpp"

class Background {
public:
    Background(sf::Vector2f pos);
    ~Background();

    void draw(sf::RenderWindow* w);

private:
    //sf::Sprite collision;
    sf::Sprite sprite;

};



#endif