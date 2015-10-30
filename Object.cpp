#include "Object.hpp"
#include "Player.hpp"

Object::Object(objectType oType, sf::Vector2f centerPosition) : Collisionable(centerPosition), _type(oType) {
    _dead = false;
    _sprite.setTexture(Resources::linkSet);
    _sprite.setTextureRect(Resources::descriptions[objectsDescription][oType][0]);
    switch (oType) {
        case halfHeal:
        case fullHeal:
            _bounds = sf::IntRect(0,0,7,8);
            _timer = 10;
            break;
        case life:
            _bounds = sf::IntRect(0,0,13,13);
            _timer = 9999999;
            break;
        case rupee:
        case rupee5:
        case key:
            _bounds = sf::IntRect(0,0,8,16);
            _timer = INT_MAX;
            break;
        case bomb:
            _bounds = sf::IntRect(0,0,8,14);
            break;
        case triforce:
        case triblue:
            _bounds = sf::IntRect(0,0,10,10);
            break;
        default:
            std::cout << "Wrong objectType at position " << centerPosition.x << " " << centerPosition.y << std::endl;
            exit(EXIT_FAILURE);
            break; // huehu
    }
    _sprite.setPosition(centerPosition.x-_bounds.left-_bounds.width/2,centerPosition.y-_bounds.top-_bounds.height/2);
}

Object::~Object() {}

void Object::update(float deltaTime) {
    _timer -= deltaTime;
    if (_timer < 0) _dead = true;
}

void Object::draw(sf::RenderTarget* target) {
    if (_timer > 2 || int(_timer*10) % 2 == 0) target->draw(_sprite);
}

objectType Object::getType() {
    return _type;
}

bool Object::isAlive() {
    return !_dead;
}

void Object::intersectsWith(Collisionable* c) {
    Player* player = dynamic_cast<Player*>(c);
    if (player != nullptr) {
        _dead = true;
    }
}
