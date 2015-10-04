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

    void draw(sf::RenderWindow *window);

    void update(float deltatime, sf::Vector2f mousePos);

    int getLifes() const;
    void setLifes(int value);

    sf::Vector2f getCenterPosition() const;
    void setCenterPosition(const sf::Vector2f &value);

    float getCenterAngle() const;

private:

    int lifes;
    int maxLifes;
    float _angle;
    sf::Vector2f velocity;
    sf::Vector2f centerPosition;

    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f &value);

};

#endif
