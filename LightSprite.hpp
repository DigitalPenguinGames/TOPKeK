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
private:
    std::vector<sf::Sprite> _sprites;
    Light* _light;
    sf::Vector2f _pos;
    directions _dir;
    int _action;
    int _currentAnimation;
    SpriteSheetDescription _description;


};

#endif