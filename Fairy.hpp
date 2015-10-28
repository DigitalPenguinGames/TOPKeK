#ifndef __FAIRY_HPP__
#define __FAIRY_HPP__

#include "utils.hpp"
#include "Effect.hpp"
#include "Resources.hpp"
#include "Collisionable.hpp"

class Fairy : public Collisionable, public Effect {

public:

    Fairy();
    ~Fairy();

    void draw(sf::RenderTarget *window);

    void update(float deltatime, sf::Vector2f mousePos);

    sf::Vector2f getCenterPosition() const;
    void setCenterPosition(const sf::Vector2f &value);

    float getCenterAngle() const;

    sf::Vector2f getPosition() const;
    sf::Vector2f getBotPosition();

    float getHp() const;
    void setHp(float value);

    void intersectsWith(Collisionable *c);
    void getHit(float qtty, sf::Vector2f);

private:

    float _hp;
    float _angle;
    float _hittedTime;
    sf::Vector2f velocity;
    sf::Vector2f centerPosition;

    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f &value);

};

#endif
