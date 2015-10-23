#include "Fairy.hpp"

Fairy::Fairy() {

    loadHorizontalSpriteSheet("Resources/Textures/fairy.png",5);
    setOrigin(8, 8);

    lifes = 3;
    maxLifes = 3;
    velocity.x = 0.0; velocity.y = 0.0;
    centerPosition.x = 0; centerPosition.y = 0;
    _bounds = sf::IntRect(3,3,10,10);

}

Fairy::~Fairy() { }

void Fairy::draw(sf::RenderTarget* window) {
    this->setColor(sf::Color(255 , 0 + (255* (lifes+0.001)/maxLifes), 0 + (255* (lifes+0.001)/maxLifes), 255));
    drawEffect(*window);
}

void Fairy::update(float deltatime, sf::Vector2f mousePos) {
    mousePos.y += 10;
    updateAnimation(deltatime);


    _angle = getAngle(centerPosition, this->Effect::getPosition());
    this->rotate(_angle - this->getRotation());

    velocity.x = 0.8*velocity.x + 0.2*(mousePos.x - this->Effect::getPosition().x ) * deltatime;
    velocity.y = 0.8*velocity.y + 0.2*(mousePos.y - this->Effect::getPosition().y ) * deltatime;
    this->move(velocity);
    _sprite.setPosition(this->Sprite::getPosition().x,this->Sprite::getPosition().y);

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

float Fairy::getCenterAngle() const{
    return _angle;
}


sf::Vector2f Fairy::getVelocity() const {
    return velocity;
}

void Fairy::setVelocity(const sf::Vector2f &value) {
    velocity = value;
}

sf::Vector2f Fairy::getPosition() const {
    return sf::Sprite::getPosition();
}

sf::Vector2f Fairy::getBotPosition() {
    return sf::Vector2f(_sprite.getPosition().x+_bounds.left+_bounds.width/2, _sprite.getPosition().y + TILESIZE);
}
