#include "FairyShoot.hpp"

FairyShoot::FairyShoot(Map* map, sf::Vector2f pos, sf::Vector2f dest, directions dir, float damage) : Weapon(map, pos, dir) {

    _sprite.setTexture(Resources::fairyShoot);
    _sprite.setOrigin(_sprite.getLocalBounds().width/2,_sprite.getLocalBounds().height/2);
    _sprite.setPosition(pos);

    //HARDCODED ALERT!!!!!!!!!!!!!!!!!!!!!!!!!!
    //NO SE PERQUE PUTA EM DONA UN DEST RARO
    //ESTIC FENT UN PUTO _PLAYER.GETPOSITION();
    dest.x = dest.x -40;
    dest.y = dest.y -35;
    _destiny = dest;
    _damage = damage;
    _lifeTime =  0.0;
    _maxLifeTime = 10;
    _speed = sf::Vector2f(10,10);
    _bounds = sf::IntRect(1,2,6,6);

    _shader = &Resources::fairyShootShader;
    Resources::fairyShootShader.setParameter("texture" , sf::Shader::CurrentTexture);
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
    Resources::fairyShootShader.setParameter("posF", getPosition());
    Resources::fairyShootShader.setParameter("posS", _destiny);
    Resources::fairyShootShader.setParameter("time",_lifeTime);
    target->draw(_sprite, _shader);
}


