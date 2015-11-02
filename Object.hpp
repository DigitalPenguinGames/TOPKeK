#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__ 

#include "utils.hpp"
#include "Resources.hpp"
#include "Collisionable.hpp"

class Scene;
class Object : public Collisionable {
public:
    Object(objectType oType, sf::Vector2f centerPosition, Scene* scene);
    ~Object();

    void update(float deltaTime);
    void draw(sf::RenderTarget* target);

    objectType getType();
    bool isAlive();

    void intersectsWith(Collisionable* c);

private:
    Scene* _scene;
    objectType _type;
    float _timer;
    bool _dead;
};










#endif