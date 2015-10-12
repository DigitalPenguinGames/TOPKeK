#ifndef __OUTSIDESCENE_HPP__
#define __OUTSIDESCENE_HPP__

#include "ScenePlayable.hpp"
#include "utils.hpp"
#include "Map.hpp"
#include "SceneChanger.hpp"
#include "Octorok.hpp"

class OutsideScene : public ScenePlayable {
friend class Game;
public:
    OutsideScene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description);
    ~OutsideScene();

    void init(sf::Vector2f sceneIniCoord);

private:
    void update(float deltaTime);
    void render(sf::RenderTarget* target);

};





#endif