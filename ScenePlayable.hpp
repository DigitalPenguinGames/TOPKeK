#ifndef __SCENEPLAYABLE_HPP__
#define __SCENEPLAYABLE_HPP__

#include "Map.hpp"
#include "utils.hpp"
#include "Fairy.hpp"
#include "Scene.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "GUI/Label.hpp"
#include "GUI/Frame.hpp"
#include "GUI/Layout.hpp"
#include "GUI/Widget.hpp"
#include "GUI/Button.hpp"
#include "GUI/VLayout.hpp"
#include "GUI/Container.hpp"
#include "GUI/ImgButton.hpp"
#include "GUI/TextButton.hpp"
#include "GUI/ImgTextButton.hpp"


class Game;
class ScenePlayable : public Scene {
public:

    ScenePlayable(Game *g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description);
    ~ScenePlayable();

    Player* getPlayer();
    void setPlayer(Player* p);

    sf::Vector2i getMapSize(); // in number of tiles
    sf::Vector2f getSceneCoord();

    void init(sf::Vector2f sceneIniCoord) = 0;

protected:
    Map _map;
    Frame _menu;
    Fairy* _fairy;
    Player* _player;
    sf::Vector2f _sceneIniCoord;
    status::gameStatus _status;
    std::list<Enemy*> _enemies;

    void renderSorted(sf::RenderTarget* target, std::vector<Collisionable*>& cols);
    void centerView();

private:
    void display();
    void processInput();

};



#endif
