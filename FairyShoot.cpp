#include "FairyShoot.hpp"

FairyShoot::FairyShoot(Map* map, sf::Vector2f pos, sf::Vector2f dest, directions dir, float damage) : Weapon(map, pos, dir) {

    _sprite.setTexture(Resources::overEnemies);
    _description = Resources::descriptions[rockProjDescription];
    _sprite.setTextureRect(_description[0][0]);
    _sprite.setPosition(pos);

    _destiny = dest;
    _damage = damage;
    _lifeTime =  0.0;
    _maxLifeTime = 10;
    _speed = sf::Vector2f(10,10);
    _bounds = sf::IntRect(1,2,6,6);
    /*Resources::sLighting.setParameter("texture" , sf::Shader::CurrentTexture);
    Resources::sLighting.setParameter("minn", 10);
    Resources::sLighting.setParameter("maxx", 900);*/
    _shader = &Resources::sLighting;
}

FairyShoot::~FairyShoot(){};

void FairyShoot::hit(){
    _dead = true;
}

void FairyShoot::update(float deltaTime){
    _lifeTime += deltaTime;
    sf::Vector2f velocity = _speed;
    velocity.x = (0.8*velocity.x + 0.2*(_destiny.x - getPosition().x )) * deltaTime;
    velocity.y = (0.8*velocity.y + 0.2*(_destiny.y - getPosition().y )) * deltaTime;
    _sprite.move(velocity);

    if( _lifeTime > _maxLifeTime || _sprite.getPosition() == _destiny){
       _dead = true;
    }
}

void FairyShoot::draw(sf::RenderTarget *target){
    target->draw(_sprite, _shader);
}


