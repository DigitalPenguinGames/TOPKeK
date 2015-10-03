#ifndef __PROJECTILE_HPP__
#define __PROJECTILE_HPP__

#include "utils.hpp"

class Projectile {
public:
	Projectile();
	~Projectile();

	void update(float deltaTime); 

private:
	sf::Vector2f speed;
	bool willDie; // When collision, the proyectile will disapear?
	float timeToDespawn;

};

#endif