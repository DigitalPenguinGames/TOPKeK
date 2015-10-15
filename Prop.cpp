#include "Prop.hpp"

Prop::Prop(int gid, sf::Vector2f pos) {
    if (gid >= 145 && gid <= 156){
        _sprite.setTexture(Resources::propsOver);
        _description = Resources::descriptions[propsOverDescription];
        _sprite.setTextureRect(_description[propTypes(gid-145)][0]);
        _sprite.setPosition(sf::Vector2f(pos.x, pos.y - 32));
        if (gid <= 150) _bounds = sf::IntRect(0,22,48,10);
        else _bounds = sf::IntRect(0, 10, 16, 6);
    }
}

Prop::~Prop() {}