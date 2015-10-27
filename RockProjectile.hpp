#ifndef __ROCKPROJECTILE_HPP__
#define __ROCKPROJECTILE_HPP__

#include "Weapon.hpp"
#include "Resources.hpp"

class RockProjectile : public Weapon {
public:
    RockProjectile(Map* map, sf::Vector2f pos, directions dir);
    ~RockProjectile();

    void update(float deltaTime);
    void draw(sf::RenderTarget* target);

    void hit();

    static sf::IntRect bounds();
private:
    sf::Transform _transform;
    float _angle;
};

#endif