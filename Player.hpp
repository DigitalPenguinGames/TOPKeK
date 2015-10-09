#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "utils.hpp"
#include "Collisionable.hpp"
#include "Resources.hpp"
#include "Projectile.hpp"
#include "LightSprite.hpp"

#define ATTACKTIMERANIMATION 0.5
#define ELAPSEDWALKING 0.18

class Player : public Collisionable {
public:
    Player();
    ~Player();
    void update(float deltaTime);
    void draw(sf::RenderTarget* w);

    void move(directions dir);
    void attack();

    sf::Vector2f getPositionTransition();
    directions getDirection();

    void setLight(Light* light);

private:
    directions _dir;
    linkActions _action;
    SpriteSheetDescription _description;
    LightSprite _lightSprite;

    float _elapsedAnimation;
    int _currentAnimation;

    bool _attacking;
    float _elapsedAttack;

    bool _moving;

    sf::IntRect _walkBounds;

    Projectile _sword;


};
#endif
