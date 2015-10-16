#include "ScenePlayable.hpp"
#include "Game.hpp"

ScenePlayable::ScenePlayable(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description) :
    Scene(g,w,sT,name),
    _map(this,description),
    _menu(*w)
{
    StatsBar* life = new StatsBar(10, Resources::heart,Resources::halfHeart,Resources::emptyHeart);
    life->setSize(sf::Vector2f(250, 50.0));
    life->setPosition(0,0);


    //setting the menu
    VLayout* layout = new VLayout;
    layout->setSpace(25);

    TextButton* resB;
    resB = new TextButton("Resume", Resources::pauseMenuFont);
    resB->onClick = [this](const sf::Event&, Button&){ _status = status::running; };
    TextButton* exitB;
    exitB = new TextButton("Exit", Resources::pauseMenuFont);
    exitB->onClick = [this](const sf::Event&, Button&){ exit(0); };
    layout->add(exitB);
    layout->add(resB);
    _menu.setLayout(layout);

    _menu.setLayout(layout);
    _menu.setPosition(0,0);

    _status = status::running;
    _fairy = new Fairy();
}

ScenePlayable::~ScenePlayable(){
}

sf::Vector2f ScenePlayable::getSceneCoord() {
    return _map.getSceneCoord();
}

sf::Vector2i ScenePlayable::getMapSize() {
    return _map.getSize();
}

Player* ScenePlayable::getPlayer() {
    return _player;
}

void ScenePlayable::setPlayer(Player* p) {
    _player = p;
}


struct CollisionPositionCompare : public std::binary_function<Collisionable*, Collisionable*, bool>
{
    bool operator()(Collisionable* c1, Collisionable* c2) const {
        float pos1 = c1->getBotPosition().y+c1->getBotPosition().x*0.01;
        float pos2 = c2->getBotPosition().y+c2->getBotPosition().x*0.01;
        return pos1 > pos2;
    }
};

void ScenePlayable::renderSorted(sf::RenderTarget* target, std::vector<Collisionable*>& cols) {
    std::priority_queue<Collisionable*, std::vector<Collisionable*>, CollisionPositionCompare> thingsToDraw;
    for (unsigned int i = 0; i < cols.size(); ++i) thingsToDraw.push(cols[i]);

    while (!thingsToDraw.empty()) {
        thingsToDraw.top()->draw(target);
        thingsToDraw.pop();
    }
}

void ScenePlayable::centerView() {
    sf::Vector2f finalPos;
    sf::Vector2f viewSize = _view.getSize();
    sf::Vector2f mapSize = sf::Vector2f(getMapSize().x * TILESIZE, getMapSize().y * TILESIZE);
    directions dir = _player->getDirection();
    sf::Vector2f speed(TILESIZE,TILESIZE);
    sf::Vector2f playerPrediction;
    playerPrediction.x = (dir == directions::left ? -speed.x : (dir == directions::right ? speed.x : 0));
    playerPrediction.y = (dir == directions::up ? -speed.y : (dir == directions::down ? speed.y : 0));
    sf::Vector2f playerPos = _player->getPositionTransition() + playerPrediction;
    
    if (mapSize.x < viewSize.x) finalPos.x = mapSize.x/2 + _sceneIniCoord.x;
    else finalPos.x = std::max(viewSize.x/2 + _sceneIniCoord.x, std::min(playerPos.x, _sceneIniCoord.x + mapSize.x - viewSize.x/2));
    if (mapSize.y < viewSize.y) finalPos.y = mapSize.y/2 + _sceneIniCoord.y;
    else finalPos.y = std::max(viewSize.y/2 + _sceneIniCoord.y, std::min(playerPos.y, _sceneIniCoord.y + mapSize.y - viewSize.y/2));

    sf::Vector2f movement = (finalPos - _view.getCenter())*(1.0f/FRAMERATE);
    _view.setCenter(_view.getCenter()+movement);

}


void ScenePlayable::display() {
    centerView();
    _window->clear();
    bool drawMenu = false;
    switch(_status){
        case status::onMenu:
            drawMenu = true;
        case status::running:
            _window->setView(_view);
            render();
            _window->setView(_window->getDefaultView());
            if(drawMenu){
                _window->draw(_menu);
            }
            break;


        default:
            break;
    }
    _window->display();
}

void ScenePlayable::processInput() {
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
        if(event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left) {
                //spawn FairyShoot;
                FairyShoot* fs;
                fs = new FairyShoot(&_map, _fairy->getPosition(), _player->getPosition(), directions::up);
                _allyWeapons.push_back(fs);
            }
        }

        if(_status == status::onMenu){
            _menu.processEvent(event);
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
    if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) _player->attack();
    if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) _player->move(directions::up);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) _player->move(directions::down);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) _player->move(directions::right);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) _player->move(directions::left);

    _fairy->setCenterPosition(sf::Vector2f(_player->getPosition()));
    _fairy->setScale(TILESIZE/_fairy->getLocalBounds().width,
                     TILESIZE/_fairy->getLocalBounds().width);
    _fairy->setOrigin(_fairy->getLocalBounds().width/2, _fairy->getLocalBounds().height/2);
    // if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) _player2->attack();
    // if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) _player2->move(directions::up);
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) _player2->move(directions::down);
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) _player2->move(directions::right);
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) _player2->move(directions::left);
    

}

void ScenePlayable::addEnemy(Enemy* enemy) {
    _enemies.push_back(enemy);
}

void ScenePlayable::addAllyWeapon(Weapon* weapon) {
    _allyWeapons.push_back(weapon);
}

void ScenePlayable::addEnemyWeapon(Weapon* weapon){
    _enemyWeapons.push_back(weapon);
}

void ScenePlayable::addForAllWeapon(Weapon* weapon){
    _forAllWeapons.push_back(weapon);
}

void ScenePlayable::addProp(Prop* prop) {
    _props.push_back(prop);
}
