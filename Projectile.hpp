#ifndef __PROJECTILE_HPP__
#define __PROJECTILE_HPP__

#include "utils.hpp"
#include "Collisionable.hpp"

class Projectile : public Collisionable {
public:
    Projectile();
    ~Projectile();

    void update(float deltaTime); 

private:
    bool willDie; // When collision, the proyectile will disapear?
    float timeToDespawn;
};

#endif