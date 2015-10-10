#ifndef __LIGHTSPRITE_HPP
#define __LIGHTSPRITE_HPP

#include "utils.hpp"
#include "Light.hpp"

class LightSprite {
public:
    LightSprite();
    LightSprite(SpriteSheetDescription description, std::vector<sf::Texture*> textures);
    ~LightSprite();

    void update(sf::Vector2f pos, int dir, int action, int currentAnimation);
    void draw(sf::RenderTarget* target);

    void setLight(Light* light);

    void setPosition(sf::Vector2f pos);
    void setRotation(float rotation);
private:
    std::vector<sf::Sprite> _sprites;
    Light* _light;
    sf::Vector2f _pos;
    float _rotation;
    directions _dir;
    int _action;
    int _currentAnimation;
    SpriteSheetDescription _description;


};

#endif