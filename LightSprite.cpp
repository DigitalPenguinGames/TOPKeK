#include "LightSprite.hpp"

LightSprite::LightSprite(){}

LightSprite::LightSprite(SpriteSheetDescription description, std::vector<sf::Texture*> textures) :
    _rotation(0),
    _description(description)
{
    _light = nullptr;
    _sprites = std::vector<sf::Sprite>(9);
    for (unsigned int i = 0; i < _sprites.size(); ++i) _sprites[i].setTexture(*textures[i]);
	_action = 0;
	_dir = directions::none;
}

LightSprite::~LightSprite() { }



void LightSprite::update( sf::Vector2f pos, int dir, int action,int currentAnimation) {
    _pos = pos;
    _dir = directions(dir);
    _action = action;
    _currentAnimation = currentAnimation;
}

void LightSprite::draw(sf::RenderTarget* target) {
    directions dir = directions::none;
    if (_light != nullptr) dir = pointsToDirection(_pos, _light->getPosition(), _rotation);
    _sprites[dir].setTextureRect(_description[_action*4+_dir][_currentAnimation%_description[_action*4+_dir].size()]);
    _sprites[dir].setPosition(_pos);
    _sprites[dir].setRotation(_rotation);
    target->draw(_sprites[dir]);
}

void LightSprite::draw(sf::RenderTarget* target, sf::Shader* shader) {
    directions dir = directions::none;
    if (_light != nullptr) dir = pointsToDirection(_pos, _light->getPosition(), _rotation);
    _sprites[dir].setTextureRect(_description[_action*4+_dir][_currentAnimation%_description[_action*4+_dir].size()]);
    _sprites[dir].setPosition(_pos);
    _sprites[dir].setRotation(_rotation);
    target->draw(_sprites[dir], shader);
}

void LightSprite::setLight(Light* light) {
    _light = light;
}

void LightSprite::setPosition(sf::Vector2f pos) {
    _pos = pos;
}

void LightSprite::setRotation(float rotation){
    _rotation = rotation;
}