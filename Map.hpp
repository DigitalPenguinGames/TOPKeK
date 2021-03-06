#ifndef __MAP_HPP__
#define __MAP_HPP__

#include "Prop.hpp"
#include "Tile.hpp"
#include "utils.hpp"
#include "Speaker.hpp"
#include "Background.hpp"
#include "DungeonDoor.hpp"
#include "SceneChanger.hpp"

class ScenePlayable;
class Map {
public:
    Map();
    Map(ScenePlayable* scene, std::string description);
    ~Map();
    void init(sf::Vector2f sceneIniCoord);
    void draw(sf::RenderTarget* w);
    void drawForeground(sf::RenderTarget* w);
    Tile* getPtrTile(sf::Vector2i pos);
    std::pair<bool,SceneChanger*> playerInsideExit(sf::Vector2f pos); // Change to Vector2f
    sf::Vector2i getSize();
    sf::Vector2f getSceneCoord();
    sf::Vector2f getMaxMovement(sf::Vector2f ini, sf::Vector2f movement, sf::IntRect rect, int8_t collisionMask, bool letGoOutside);

    std::list<std::pair<DungeonDoor*,directions> > getDungeonDoors();

private:
    ScenePlayable* _scene;
    std::vector<std::vector<int> > _premap;
    std::vector<std::vector<Tile> > _map; // If sceneType == outside
    std::unique_ptr<Background> _background;               // If sceneType == dungeon
    std::vector<SceneChanger> _sceneChangers;
    sf::Vector2f _mapIniCoord;
    int _mapType;
    sf::Image _collisionBackground;
    sf::Sprite _foreground;
    std::list<std::pair<DungeonDoor*,directions> > _dungeonDoors;
};

#endif
