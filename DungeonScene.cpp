#include "DungeonScene.hpp"
#include "Game.hpp"

DungeonScene::DungeonScene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description) :
    ScenePlayable(g,w,sT,name,description)
{
    _sceneIniCoord = sf::Vector2f(FLT_MAX,FLT_MAX);
}

DungeonScene::~DungeonScene() {

}

void DungeonScene::init(sf::Vector2f sceneIniCoord = sf::Vector2f(0,0)) {
    ScenePlayable::init(sceneIniCoord);
}

void DungeonScene::update(float deltaTime) {
    ScenePlayable::update(deltaTime);
}

void DungeonScene::render(sf::RenderTarget* target) {
    ScenePlayable::render(target);
}

sceneTypes DungeonScene::getType(){
    return sceneTypes::dungeon;
}