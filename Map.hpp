#ifndef __MAP_HPP__
#define __MAP_HPP__

#include "utils.hpp"
#include "Tile.hpp"
#include "SceneChanger.hpp"
#include "Background.hpp"
#include "Prop.hpp"

class ScenePlayable;
class Map {
public:
    Map(ScenePlayable* scene, std::string description);
    ~Map();
    void init(sf::Vector2f sceneIniCoord);
    void draw(sf::RenderTarget* w);
    Tile* getPtrTile(sf::Vector2i pos);
    std::pair<bool,SceneChanger*> playerInsideExit(sf::Vector2f pos); // Change to Vector2f
    sf::Vector2i getSize();
    sf::Vector2f getSceneCoord();
    sf::Vector2f getMaxMovement(sf::Vector2f ini, sf::Vector2f movement, sf::IntRect rect);;
private:
    ScenePlayable* _scene;
    std::vector<std::vector<int> > _premap;
    std::vector<std::vector<Tile> > _map; // If sceneType == outside
    Background* _background;               // If sceneType == dungeon
    std::vector<SceneChanger> _sceneChangers;
    sf::Vector2f _mapIniCoord;
    int _mapType;
    sf::Image _collisionBackground;
};

#endif