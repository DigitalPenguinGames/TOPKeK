#ifndef FAIRYSHOOT_HPP
#define FAIRYSHOOT_HPP

#include "utils.hpp"
#include "Weapon.hpp"

class FairyShoot : public Weapon{

public:
    FairyShoot(Map* map, sf::Vector2f pos, sf::Vector2f dest, directions dir, float damage = 1);
    ~FairyShoot();

    void hit();
    void update(float deltaTime);
    void draw(sf::RenderTarget* target);

private:

    float _lifeTime;
    float _maxLifeTime;
    sf::Sprite _sprite;
    sf::Shader* _shader;
    sf::Vector2f _destiny;

};

#endif // FAIRYSHOOT_HPP
