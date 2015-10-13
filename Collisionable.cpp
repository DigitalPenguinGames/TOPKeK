#include "Collisionable.hpp"

Collisionable::Collisionable(sf::Vector2f position) {
    _sprite.setPosition(position);
}

Collisionable::~Collisionable() {}

void Collisionable::update(float deltaTime) {
    (void) deltaTime;
}

void Collisionable::draw(sf::RenderTarget* window) {
    window->draw(_sprite);
}

bool Collisionable::collisioning(Collisionable* c1, Collisionable* c2) {
    sf::Vector2f pos1 = c1->getPosition(), pos2 = c2->getPosition();
    sf::IntRect rec1 = c1->getBounds(), rec2 = c2->getBounds();
    sf::FloatRect aux1(pos1.x+rec1.left, pos1.y+rec1.top, rec1.width, rec1.height);
    sf::FloatRect aux2(pos2.x+rec2.left, pos2.y+rec2.top, rec2.width, rec2.height);
    return aux1.intersects(aux2);
}

sf::Vector2f Collisionable::getPosition() {
    return _sprite.getPosition();
}

sf::IntRect Collisionable::getGlobalBound() {
    return sf::IntRect(_sprite.getPosition().x + _bounds.left, _sprite.getPosition().y + _bounds.top, _bounds.width, _bounds.height);
}

sf::IntRect Collisionable::getBounds() {
    return _bounds;
}

void Collisionable::setPosition(sf::Vector2f pos) {
    _sprite.setPosition(pos);
}
sf::Vector2f Collisionable::getBotPosition() {
    return sf::Vector2f(_sprite.getPosition().x+_bounds.left+_bounds.width/2, _sprite.getPosition().y + _bounds.top+_bounds.height);
}