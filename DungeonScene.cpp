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

void DungeonScene::processInput() {
    sf::Event event;
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            _window->close(); exit(0);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
            if(_status == status::running) _status = status::onMenu;
            else _status = status::running;
        }
        //else if (event.type == sf::Event::Resized) initView();
    }

    // Debug change scene
    sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window),_view);
    //std::cout << "mouse position " << mousePos.x << " " << mousePos.y << std::endl;
    std::pair<bool,SceneChanger*> aux = _map.playerInsideExit(mousePos);
    if (aux.first) {
        changeScene(aux.second);
    }

    // Debug link movement
    if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) _player->attack();
    if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) _player->move(directions::up);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) _player->move(directions::down);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) _player->move(directions::right);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) _player->move(directions::left);

    // if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) _player2->attack();
    // if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) _player2->move(directions::up);
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) _player2->move(directions::down);
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) _player2->move(directions::right);
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) _player2->move(directions::left);
    

}

void DungeonScene::update(float deltaTime) {
    //(void)deltaTime;
    _player->update(deltaTime);
}

void DungeonScene::render() {
    _map.draw(_window);
    // Drawing the dinamic things
    std::vector<Collisionable*> collisionables;
    collisionables.push_back(_player);

    renderSorted(collisionables);

    //_player->draw(_window);
}