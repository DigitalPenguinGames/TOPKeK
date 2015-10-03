#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "utils.hpp"
#include "Collisionable.hpp"
#include "Resources.hpp"

#define ATTACKTIMERANIMATION 0.5
#define ELAPSEDWALKING 0.18

class Player : public Collisionable {
public:
    Player();
    ~Player();
    void update(float deltaTime);
    void draw(sf::RenderWindow* w);

    void move(directions dir);
    void attack();

private:
    directions _dir;
    linkActions _action;
    SpriteSheetDescription _description;

    float _elapsedAnimation;
    int _currentAnimation;

    bool _attacking;
    float _elapsedAttack;

    bool _moving;


};
#endif
