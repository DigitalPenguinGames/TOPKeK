#include "Fairy.hpp"

Fairy::Fairy() {

    lifes = 3;
    maxLifes = 3;
    velocity.x = 50; velocity.y = 50;
    centerPosition.x = 0; centerPosition.y = 0;
}

Fairy::~Fairy() { }

void Fairy::draw(sf::RenderWindow window) {
    this->setColor(sf::Color(255 - (255* (lifes+0.001)/maxLifes), 0, 0));
    this->Effect::draw(window);
}

void Fairy::update(float deltatime, sf::Vector2f mousePos) {
    sf::Vector2f pos = this->Effect::getPosition();
    float angle = getAngle(pos, mousePos);
    this->rotate(angle - this->getRotation());
    sf::Vector2f movement;
    movement.x = std::cos(angle)*velocity.x *deltatime;
    movement.y = std::cos(angle)*velocity.y *deltatime;
    this->move(movement);
}

int Fairy::getLifes() const {
    return lifes;
}

void Fairy::setLifes(int value) {
    if (value > maxLifes) maxLifes = value;
    lifes = value;
}

sf::Vector2f Fairy::getCenterPosition() const {
    return centerPosition;
}

void Fairy::setCenterPosition(const sf::Vector2f &value) {
    centerPosition = value;
}

sf::Vector2f Fairy::getVelocity() const {
    return velocity;
}

void Fairy::setVelocity(const sf::Vector2f &value) {
    velocity = value;
}


