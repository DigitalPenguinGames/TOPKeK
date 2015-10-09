#include "LightedDungeonScene.hpp"

LightedDungeonScene::LightedDungeonScene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description):
    DungeonScene(g,w,sT,name,description) {

}

LightedDungeonScene::~LightedDungeonScene() {}

void LightedDungeonScene::init(sf::Vector2f sceneIniCoord) {
    DungeonScene::init(sceneIniCoord);
    _light.setPosition(sceneIniCoord + sf::Vector2f(100,100));
    _texture.create(DUNGEONSIZEX,DUNGEONSIZEY);

    Resources::sLighting.setParameter("texture", sf::Shader::CurrentTexture);
    Resources::sLighting.setParameter("min", 100);
    Resources::sLighting.setParameter("max", 400);
}

void LightedDungeonScene::render(sf::RenderTarget* target) {
    sf::View auxView = _view;
    auxView.setViewport(sf::FloatRect(0,0,1,1)); // Change the viewport to avoid cuttin the scene
    _texture.setView(auxView); // I need the view to draw in the renderTexture correctly
    DungeonScene::render(&_texture);
    _texture.setView(_window->getDefaultView());
    _texture.display();
    sf::Sprite aux(_texture.getTexture());
    aux.setPosition(_sceneIniCoord);

    sf::Vector2f lightPos(_window->mapCoordsToPixel(_fairy->getPosition(),_view));
    lightPos.y = _window->getSize().y - lightPos.y;
    Resources::sLighting.setParameter("posLight", lightPos);
    target->draw(aux, &Resources::sLighting);
}