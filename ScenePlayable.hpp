#ifndef __SCENEPLAYABLE_HPP__
#define __SCENEPLAYABLE_HPP__

#include "Map.hpp"
#include "Prop.hpp"
#include "utils.hpp"
#include "Fairy.hpp"
#include "Scene.hpp"
#include "Enemy.hpp"
#include "Octorok.hpp"
#include "EnemyPenguin.hpp"
#include "Player.hpp"
#include "Weapon.hpp"
#include "Object.hpp"
#include "StatsBar.hpp"
#include "GUI/Label.hpp"
#include "GUI/Frame.hpp"
#include "FairyShoot.hpp"
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

    void init(sf::Vector2f sceneIniCoord);
    void update(float deltaTime);
    void render(sf::RenderTarget* target);

    void addEnemy(Enemy* enemy);
    void addAllyWeapon(Weapon* weapon);
    void addEnemyWeapon(Weapon* weapon);
    void addForAllWeapon(Weapon* weapon);
    void addProp(Collisionable* prop);
    void addObject(Object* object);

protected:
    std::list<Enemy*> _enemies;
    std::list<Weapon*> _allyWeapons;
    std::list<Weapon*> _enemyWeapons;
    std::list<Weapon*> _forAllWeapons;
    std::list<Collisionable*> _props;
    std::list<Object*> _objects;

    sf::Vector2f _sceneIniCoord;
    Map _map;
    Fairy* _fairy;
    Player* _player;

    status::gameStatus _status;
    Frame _menu;
    float _elapsedPress;
    int _buttonSelected;
    VLayout* _menuLayout;
    VLayout* _selectedLayout;
    Frame _hud;
    StatsBar* _life;
    StatsBar* _rupias;
    VLayout* _guiLayout;

    void clearMap();

    void updateHUD();

    void renderSorted(sf::RenderTarget* target, std::vector<Collisionable*>& cols);
    void centerView();

private:
    void display();
    void processInput();

};



#endif
