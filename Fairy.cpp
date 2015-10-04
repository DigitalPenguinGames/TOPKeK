#include "Fairy.hpp"

Fairy::Fairy() {

    loadHorizontalSpriteSheet("Resources/Textures/fairy.png",5);
    setOrigin(getGlobalBounds().width/2, getGlobalBounds().height/2);

    lifes = 3;
    maxLifes = 3;
    velocity.x = 50; velocity.y = 50;
    centerPosition.x = 0; centerPosition.y = 0;
}

Fairy::~Fairy() { }

void Fairy::draw(sf::RenderWindow* window) {
    //this->setColor(sf::Color(255 - (255* (lifes+0.001)/maxLifes), 0, 0));
    drawEffect(*window);
}

void Fairy::update(float deltatime, sf::Vector2f mousePos) {
    updateAnimation(deltatime);

    float prevAngle = _angle;

    _angle = getAngle(centerPosition, this->Effect::getPosition());
    this->rotate(_angle - this->getRotation());


    _angle = getAngle(this->Effect::getPosition(), mousePos);

    sf::Vector2f movement;
    std::cout << " angle : " <<_angle << std::endl;

    if(getModule(this->Effect::getPosition(), mousePos) > float(TILESIZE)  ){
        movement.y = std::sin(_angle)*velocity.y *deltatime;
        movement.x = std::cos(_angle)*velocity.x *deltatime;
    } else movement.x = movement.y = 0;
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

float Fairy::getCenterAngle() const{
    return _angle;
}


sf::Vector2f Fairy::getVelocity() const {
    return velocity;
}

void Fairy::setVelocity(const sf::Vector2f &value) {
    velocity = value;
}


