#include "Fairy.hpp"
#include "Enemy.hpp"
#include "Weapon.hpp"

Fairy::Fairy() {

    loadHorizontalSpriteSheet("Resources/Textures/fairy.png",5);
    setOrigin(8, 8);

    _hp = 0;
    velocity.x = 0.0; velocity.y = 0.0;
    centerPosition.x = 0; centerPosition.y = 0;
    _bounds = sf::IntRect(-5,-5,10,10);

}

Fairy::~Fairy() { }

void Fairy::draw(sf::RenderTarget* window) {
    //deprecated
    //this->setColor(sf::Color(255 , 0 + (255* (lifes+0.001)/maxLifes), 0 + (255* (lifes+0.001)/maxLifes), 255));
    if( _hittedTime < 1 ) {
        if(int(_hittedTime*10) %2) drawEffect(*window);
    } else drawEffect(*window);
}

void Fairy::update(float deltatime, sf::Vector2f mousePos) {
    updateAnimation(deltatime);

    _hittedTime += deltatime;

    _angle = getAngle(centerPosition, this->Effect::getPosition());
    this->rotate(_angle - this->getRotation());

    velocity.x = 0.8*velocity.x + 0.2*(mousePos.x - this->Effect::getPosition().x ) * deltatime;
    velocity.y = 0.8*velocity.y + 0.2*(mousePos.y - this->Effect::getPosition().y ) * deltatime;
    this->move(velocity);
    cmove(velocity);

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
float Fairy::getHp() const{
    return _hp;
}

void Fairy::setHp(float value){
    _hp = value;
}


void Fairy::getHit(float qtty, sf::Vector2f){
    if(_hittedTime < 1) return;
    _hittedTime = 0;
    _hp -= qtty;
}

void Fairy::intersectsWith(Collisionable* c) {
    Enemy* enemy = dynamic_cast<Enemy*>(c);
    if (enemy != nullptr) {
        getHit(enemy->getDamage(),sf::Vector2f(0,0));
        return;
    }

    Weapon* weapon = dynamic_cast<Weapon*>(c);
    if (weapon != nullptr) {
        getHit(weapon->getDamage(),sf::Vector2f(0,0));
        return;
    }
}
