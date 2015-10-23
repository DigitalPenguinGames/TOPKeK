#include "OutsideScene.hpp"
#include "Game.hpp"

OutsideScene::OutsideScene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description) :
    ScenePlayable(g,w,sT,name,description)
{

    //std::cout << &(*w) << std::endl;
    _sceneIniCoord = sf::Vector2f(FLT_MAX,FLT_MAX);
}

OutsideScene::~OutsideScene() {

}






