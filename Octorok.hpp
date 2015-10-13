#ifndef __OCTOROK_HPP__
#define __OCTOROK_HPP__

#include "Enemy.hpp"
#include "Resources.hpp"
#include "RockProjectile.hpp"

class Octorok : public Enemy {
public:
    Octorok(ScenePlayable* scene,Map* map, sf::Vector2f pos);
    ~Octorok();

    void update(float deltaTime);
    sf::Vector2f getBotPosition();

private:
    float _time;
};

#endif