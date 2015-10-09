#ifndef __LIGHTDUNGEONSCENE_HPP__
#define __LIGHTDUNGEONSCENE_HPP__

#include "utils.hpp"
#include "Light.hpp"
#include "DungeonScene.hpp"

class Game;
class LightedDungeonScene : public DungeonScene {
public:
    LightedDungeonScene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description);
    ~LightedDungeonScene();

    void init(sf::Vector2f sceneIniCoord);
private:
    Light _light;
    sf::RenderTexture _texture;
    void render(sf::RenderTarget* target);
};

#endif