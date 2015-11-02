#ifndef __BACKGROUND_HPP__
#define __BACKGROUND_HPP__

#include "utils.hpp"
#include "Resources.hpp"

class Background {
public:
    Background(sf::Vector2f pos);
    ~Background();

    void draw(sf::RenderTarget* w);

private:
    //sf::Sprite collision;
    sf::Sprite _sprite;
    sf::Sprite _decoration;
    bool _dec;

};



#endif
