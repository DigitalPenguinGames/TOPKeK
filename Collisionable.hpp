#ifndef __COLLISIONABLE_HPP__
#define __COLLISIONABLE_HPP__

#include "utils.hpp"

class Collisionable {
 public:
 	Collisionable(sf::Vector2f speed = sf::Vector2f(0,0));
 	~Collisionable();
 	virtual void update(float deltaTime);
 	virtual void draw(sf::RenderWindow* window);

 	static bool collisioning(Collisionable* c1, Collisionable* c2);

 	sf::Vector2f getPosition();
 	sf::IntRect getBounds();

 protected:
 	sf::Sprite _sprite;
 	sf::Vector2f _speed;
 	sf::IntRect _bounds; // IntRect(offset.x, offset.y, width, height)
 }; 


#endif