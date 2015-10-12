#ifndef __PROJECTILE_HPP__
#define __PROJECTILE_HPP__

#include "utils.hpp"
#include "Collisionable.hpp"
#include "Resources.hpp"
#include "LightSprite.hpp"

class Projectile : public Collisionable {
public:
    Projectile();
    ~Projectile();

    void init(directions dir, sf::Vector2f pos);

    void update(float deltaTime); 

    void draw(sf::RenderTarget* w);

    void setPosition(sf::Vector2f pos);
    void setLight(Light* light);

protected:
    LightSprite _lightSprite;
    bool willDie; // When collision, the proyectile will disapear?
    float timeToDespawn;
    float deltaToDespawn;
};

#endif