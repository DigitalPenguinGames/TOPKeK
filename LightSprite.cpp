#include "LightSprite.hpp"

LightSprite::LightSprite(){}

LightSprite::LightSprite(SpriteSheetDescription description, std::vector<sf::Texture*> textures) :
    _description(description)
{
    _light = nullptr;
    _sprites = std::vector<sf::Sprite>(9);
    for (unsigned int i = 0; i < _sprites.size(); ++i) _sprites[i].setTexture(*textures[i]);
}

LightSprite::~LightSprite() {}



void LightSprite::update( sf::Vector2f pos, int dir, int action,int currentAnimation) {
    _pos = pos;
    _dir = directions(dir);
    _action = action;
    _currentAnimation = currentAnimation;
}

void LightSprite::draw(sf::RenderTarget* target) {
    if (_light == nullptr) {
        _sprites[directions::none].setTextureRect(_description[_action*directionsQtty+_dir][_currentAnimation%_description[_action*directionsQtty+_dir].size()]);
        _sprites[directions::none].setPosition(_pos);
        target->draw(_sprites[directions::none]);
    }
    else {
        directions dir = pointsToDirection(_pos, _light->getPosition());
        _sprites[dir].setTextureRect(_description[_action*directionsQtty+_dir][_currentAnimation%_description[_action*directionsQtty+_dir].size()]);
        _sprites[dir].setPosition(_pos);
        target->draw(_sprites[dir]);
    }
}

void LightSprite::setLight(Light* light) {
    _light = light;
}