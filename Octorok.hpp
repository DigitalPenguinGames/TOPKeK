#ifndef __OCTOROK_HPP__
#define __OCTOROK_HPP__

#include "Enemy.hpp"
#include "Resources.hpp"

class Octorok : public Enemy {
public:
    Octorok(Map* map, sf::Vector2f pos);
    ~Octorok();

    void update(float deltaTime);
private:
    float _time;
};

#endif