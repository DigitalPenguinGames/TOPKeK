#ifndef ENEMYPENGUIN_HPP
#define ENEMYPENGUIN_HPP
#include "Enemy.hpp"
#include "utils.hpp"
#include "Resources.hpp"

class EnemyPenguin : public Enemy {

public:
    EnemyPenguin(ScenePlayable* scene, Map* map, sf::Vector2f pos);

    sf::Vector2f getBotPosition();
    void update(float deltaTime);

private:
    float _time;
    bool _preparing;
    bool _attacking;

    void setPrep();
    void setWalk();
    void setAttack();
};

#endif // ENEMYPENGUIN_HPP
