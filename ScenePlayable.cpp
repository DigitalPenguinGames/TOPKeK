#include "ScenePlayable.hpp"
#include "Game.hpp"

ScenePlayable::ScenePlayable(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description) :
    Scene(g,w,sT,name),
    _map(this,description),
    _menu(*w),
    _hud(*w)
{
    _sceneIniCoord = sf::Vector2f(FLT_MAX,FLT_MAX);

    _life = new StatsBar(10, Resources::heart,Resources::halfHeart,Resources::emptyHeart);
    _life->setSize(sf::Vector2f(250, 50.0));
    _life->setPosition(0,0);


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

    _hud.setLayout(_life);
    _hud.setPosition(0,0);


    _status = status::running;
    _fairy = new Fairy();
}

ScenePlayable::~ScenePlayable(){
}

void ScenePlayable::init(sf::Vector2f sceneIniCoord = sf::Vector2f(0,0)) {
    _player->setMap(&_map);
    if (sceneIniCoord == _sceneIniCoord) return;
    _sceneIniCoord = sceneIniCoord;
    _map.init(_sceneIniCoord);
    initView(sf::Vector2i(WINDOWRATIOX,WINDOWRATIOY));
    _enemies.push_back(new Octorok(this, &_map, sf::Vector2f(70+sceneIniCoord.x,70+sceneIniCoord.y)));
    _life->setMaxHP(_player->getMaxHp());
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
            Scene::render();
            _window->setView(_window->getDefaultView());
            _window->draw(_hud);
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
                                    //_player->getPosition(), directions::up);
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

void ScenePlayable::update(float deltaTime) {
    _player->update(deltaTime);
    _fairy->update(deltaTime, sf::Vector2f(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window),_view)));
    _fairy->setCenterPosition(sf::Vector2f(_player->getPosition()));
    for (auto it = _enemies.begin(); it != _enemies.end(); ++it) (*it)->update(deltaTime);
    for (auto it = _enemyWeapons.begin(); it != _enemyWeapons.end(); ++it) (*it)->update(deltaTime);
    for (auto it = _allyWeapons.begin(); it != _allyWeapons.end(); ++it) (*it)->update(deltaTime); 
    for (auto it = _forAllWeapons.begin(); it != _forAllWeapons.end(); ++it) (*it)->update(deltaTime);
    // Collisiones & things
    std::pair<bool,SceneChanger*> aux = _map.playerInsideExit(_player->getPositionTransition());
    if (aux.first) {
        changeScene(aux.second);
    }

    if (_player->isAttacking()/*&& _player.isUsingSword*/) {
        sf::IntRect swordRect = _player->getSwordRect();
        for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
            if (swordRect.intersects((*it)->getGlobalBound())){
                (*it)->getHit(_player->getSwordDamage(), sf::Vector2f(0,0));
            }
        } 
    }
    // Collisions between player and things

    sf::IntRect playerBound = _player->getGlobalBound();
    for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
        if (playerBound.intersects((*it)->getGlobalBound())) _player->getHit((*it)->getDamage(),(*it)->getPosition());
    }
    for (auto it = _enemyWeapons.begin(); it != _enemyWeapons.end(); ++it) {
        if (playerBound.intersects((*it)->getGlobalBound())) {
            if (!counterDirection(_player->getDirection(),(*it)->getDirection()) || _player->isAttacking()) 
                _player->getHit((*it)->getDamage(),(*it)->getPosition());
            (*it)->hit();
        }
    }
    for (auto it = _forAllWeapons.begin(); it != _forAllWeapons.end(); ++it) {
        if (playerBound.intersects((*it)->getGlobalBound())) _player->getHit((*it)->getDamage(),(*it)->getPosition());
    }
    sf::IntRect playerWalkBounds = _player->getGlobalWalkBounds();
    for (auto it = _props.begin(); it != _props.end(); ++it) {
        // here will be like player->colwithprop(gid) prop->collisionwithplayer
        if (playerWalkBounds.intersects((*it)->getGlobalBound())) _player->resetMove();
    }
    // Collision between object(rupies, arrows, bombs);

    // Collisions between Enemies and things
    for (auto enemyIt = _enemies.begin(); enemyIt != _enemies.end(); ++enemyIt) {
        sf::IntRect bounds = (*enemyIt)->getGlobalBound();
        for (auto it = _allyWeapons.begin(); it != _allyWeapons.end(); ++it) {
            if (bounds.intersects((*it)->getGlobalBound())) (*enemyIt)->getHit((*it)->getDamage(),(*it)->getPosition());
        }
        for (auto it = _forAllWeapons.begin(); it != _forAllWeapons.end(); ++it) {
            if (bounds.intersects((*it)->getGlobalBound())) (*enemyIt)->getHit((*it)->getDamage(),(*it)->getPosition());
        }

        sf::IntRect enemyWalkBounds = (*enemyIt)->getGlobalWalkBounds();
        for (auto it = _props.begin(); it != _props.end(); ++it) {
            if (enemyWalkBounds.intersects((*it)->getGlobalBound())) (*enemyIt)->resetMove();
        }
        // Collisions between rocks & co
    }

    // Collisions between weapons & props
    for (auto weaponIt = _enemyWeapons.begin(); weaponIt != _enemyWeapons.end(); ++weaponIt) {
        sf::IntRect bounds = (*weaponIt)->getGlobalBound();
        for (auto it = _props.begin(); it != _props.end(); ++it) {
            if (bounds.intersects((*it)->getGlobalBound())) (*weaponIt)->hit();
        }
    }

    for (auto weaponIt = _allyWeapons.begin(); weaponIt != _allyWeapons.end(); ++weaponIt) {
        sf::IntRect bounds = (*weaponIt)->getGlobalBound();
        for (auto it = _props.begin(); it != _props.end(); ++it) {
            if (bounds.intersects((*it)->getGlobalBound())) (*weaponIt)->hit();
        }
    }

    for (auto weaponIt = _forAllWeapons.begin(); weaponIt != _forAllWeapons.end(); ++weaponIt) {
        sf::IntRect bounds = (*weaponIt)->getGlobalBound();
        for (auto it = _props.begin(); it != _props.end(); ++it) {
            if (bounds.intersects((*it)->getGlobalBound())) (*weaponIt)->hit();
        }
    }

    // Are all the shits alive?
    {
        for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
            if (!(*it)->isAlive()) {
                delete (*it);
                it = _enemies.erase(it);
                --it;
            }
        }
        for (auto it = _enemyWeapons.begin(); it != _enemyWeapons.end(); ++it) {
            if (!(*it)->isAlive()) {
                delete (*it);
                it = _enemyWeapons.erase(it);
                --it;
            }
        }
        for (auto it = _allyWeapons.begin(); it != _allyWeapons.end(); ++it) {
            if (!(*it)->isAlive()) {
                delete (*it);
                it = _allyWeapons.erase(it);
                --it;
            }
        }
        for (auto it = _forAllWeapons.begin(); it != _forAllWeapons.end(); ++it) {
            if (!(*it)->isAlive()) {
                delete (*it);
                it = _forAllWeapons.erase(it);
                --it;
            }
        }
        // Objects (rupies, shit)
    }

    _life->setActualHP(_player->getHp());

}


void ScenePlayable::render(sf::RenderTarget* target) {
    _map.draw(target);
    // Drawing the dinamic things
    std::vector<Collisionable*> collisionables;
    collisionables.push_back(_player);
    collisionables.push_back(_fairy);
    for (auto it = _enemies.begin(); it != _enemies.end(); ++it) collisionables.push_back(*it);
    for (auto it = _enemyWeapons.begin(); it != _enemyWeapons.end(); ++it) collisionables.push_back(*it);
    for (auto it = _allyWeapons.begin(); it != _allyWeapons.end(); ++it) collisionables.push_back(*it);
    for (auto it = _forAllWeapons.begin(); it != _forAllWeapons.end(); ++it) collisionables.push_back(*it);
    for (auto it = _props.begin(); it != _props.end(); ++it) collisionables.push_back(*it);
    renderSorted(target, collisionables);
}
