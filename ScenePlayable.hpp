#ifndef __SCENEPLAYABLE_HPP__
#define __SCENEPLAYABLE_HPP__

#include "Map.hpp"
#include "utils.hpp"
#include "Fairy.hpp"
#include "Scene.hpp"
#include "Player.hpp"

class Game;
class ScenePlayable : public Scene {
public:

    ScenePlayable(Game *g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description);
	~ScenePlayable();

    Player* getPlayer();
    void setPlayer(Player* p);

    sf::Vector2i getMapSize();
    sf::Vector2f getSceneCoord();

    void init(sf::Vector2f sceneIniCoord) = 0;

protected:
	Map _map;
    Fairy* _fairy;
    Player* _player;
	sf::Vector2f _sceneIniCoord;
    status::gameStatus _status;

    void renderSorted(std::vector<Collisionable*>& cols);

private:
	void display();

};



#endif
