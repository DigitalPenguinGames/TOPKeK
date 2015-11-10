#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Resources.hpp"
#include "Scene.hpp"
#include "SceneMenu.hpp"
#include "utils.hpp"
#include "DungeonScene.hpp"
#include "LightedDungeonScene.hpp"
#include "SceneChanger.hpp"


class Game {
friend class SceneMenu;
friend class SceneCutScene;
public:
    Game();
    ~Game();

    void start();

    void changeScene(SceneChanger* sC);


private:
    sf::RenderWindow _window;
    std::map<std::string, Scene*> _scenes;
    Scene* _currentScene;
    Scene* _lastScene;

    sf::Mutex _mutex;
    sf::Thread* _thread;

    void loadScenes();
    void loadScene(std::string sceneName);

    void initInput();
};

#endif