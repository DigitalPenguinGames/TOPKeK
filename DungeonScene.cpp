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
    if (sceneIniCoord == _sceneIniCoord) return;
    _sceneIniCoord = sceneIniCoord;
    _map.init(_sceneIniCoord);
    initView(sf::Vector2i(WINDOWRATIOX,WINDOWRATIOY));
}

void DungeonScene::update(float deltaTime) {
    //(void)deltaTime;

    _player->update(deltaTime);
    _fairy->update(deltaTime, sf::Vector2f(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window),_view)));

    // Collisiones & things
    std::pair<bool,SceneChanger*> aux = _map.playerInsideExit(_player->getPositionTransition());
    if (aux.first) {
        changeScene(aux.second);
    }
}

void DungeonScene::render(sf::RenderTarget* target) {
    _map.draw(target);
    // Drawing the dinamic things
    std::vector<Collisionable*> collisionables;
    collisionables.push_back(_player);
    collisionables.push_back(_fairy);

    renderSorted(target, collisionables);
}

sceneTypes DungeonScene::getType(){
    return sceneTypes::dungeon;
}