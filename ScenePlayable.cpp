#include "ScenePlayable.hpp"
#include "Game.hpp"

ScenePlayable::ScenePlayable(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description) :
    Scene(g,w,sT,name),
    _map(this,description),
    _menu(*w,_viewUI),
    _hud(*w,_viewUI)
{
    _sceneIniCoord = sf::Vector2f(FLT_MAX,FLT_MAX);
    //setting the menu
    _menuLayout = new VLayout;
    _menuLayout->setSpace(25);

    TextButton* resB;
    resB = new TextButton("    Resume", Resources::pauseMenuFont);
    resB->onClick = [this](const sf::Event&, Button&){ _status = status::running; };
    TextButton* exitB;
    exitB = new TextButton("    Menu", Resources::pauseMenuFont);
    exitB->onClick = [this](const sf::Event&, Button&){changeScene(new SceneChanger(sf::Vector2f(0,0), "menu", sf::Vector2f(0,0)));  };
    _menuLayout->add(exitB);
    _menuLayout->add(resB);
    _menu.setLayout(_menuLayout);


    _guiLayout = new VLayout;
    _guiLayout->setCentered(false);
    _guiLayout->setPosition(0,0);
    _guiLayout->setSpace(1);

    _life = new StatsBar(10, Resources::heart,Resources::halfHeart,Resources::emptyHeart);
    _life->setSize(sf::Vector2f(250, 50.0));
    _life->setPosition(0,0);

    _space = new ImgButton(Resources::emptyHeart,Resources::emptyHeart);
    _space->setSize(sf::Vector2f(0, 330));
    _space->setPosition(200,0);
    //ok there is no space widget, get over it!

    _items = new HLayout(_guiLayout);
    _qttyKeys = new Label("0", Resources::pauseMenuFont, _items);
    _qttyRupias = new Label("0", Resources::pauseMenuFont, _items);
    _key = new ImgButton(Resources::key, Resources::key, _items);
    _key->setSize(50,50);
    _rupia = new ImgButton(Resources::rupia, Resources::rupia, _items);
    _rupia->setSize(50,50);
    _items->setSpace(20);
    _items->add(_qttyRupias);
    _items->add(_rupia);
    _items->add(_qttyKeys);
    _items->add(_key);

    _guiLayout->add(_life);
    _guiLayout->add(_space);
    _guiLayout->add(_items);

    _hud.setLayout(_guiLayout);
    _hud.setPosition(0,0);


    _status = status::running;
    _elapsedPress = 0;
    _fairy = new Fairy();
    _player = nullptr;
}

ScenePlayable::~ScenePlayable(){}

void ScenePlayable::init(sf::Vector2f sceneIniCoord = sf::Vector2f(0,0)) {
    clearMap();
    _player->setMap(&_map);
    _life->setMaxHP(_player->getMaxHp());
    initEnemies(sceneIniCoord);
    _status = status::running;
	resizing();
	if (sceneIniCoord == _sceneIniCoord) return;
    _sceneIniCoord = sceneIniCoord;
    _map.init(_sceneIniCoord);
	resizing();
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

void ScenePlayable::centerView(bool hard) {
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

    sf::Vector2f movement;
    if (hard) {
        movement = finalPos - _view.getCenter();
        _viewUI.setCenter(_viewUI.getSize().x/2, _viewUI.getSize().y/2);
		initMenu();
    }
    else movement = (finalPos - _view.getCenter())*(1.0f/FRAMERATE);
    _view.setCenter(_view.getCenter()+movement);

}


void ScenePlayable::display() {
    centerView(false);
    _window->clear();
    bool drawMenu = false;
    switch(_status){
        case status::onMenu:
            drawMenu = true;
        case status::running:
            _window->setView(_view);
            Scene::render();
            _window->setView(_viewUI);
            _window->draw(_hud);
            if(drawMenu){
                _window->setMouseCursorVisible(true);
                _window->draw(_menu);
            }else {
                _window->setMouseCursorVisible(false);
            }

            _window->setView(_window->getDefaultView());
            break;


        default:
            break;
    }
    _window->display();
}

void ScenePlayable::processInput() {
    InputManager::update();
    sf::Event event;

    switch (_status) {
        case status::onMenu:{
            while (_window->pollEvent(event)) {
                TextBoxManager::processEvent(event);
                _menu.processEvent(event);
                if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
                else if (event.type == sf::Event::Resized) {
					resizing();
                }
                else if (event.type == sf::Event::LostFocus) _focus = false;
                else if (event.type == sf::Event::MouseMoved) {
                    _window->setMouseCursorVisible(true);
                    if (_buttonSelected >= 0) static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseLeft();
                    _buttonSelected = -1;

                }
            }
            if (_elapsedPress < 0.3) return;
            if (InputManager::action(InputAction::pause)) {
                _elapsedPress = 0;
                if(_status == status::running) _status = status::onMenu;
                else _status = status::running;
            }
            if (InputManager::action(InputAction::menuDown)) {
                _elapsedPress = 0;
                _window->setMouseCursorVisible(false);

                if (_buttonSelected >= 0) static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseLeft();
                _buttonSelected = (((_buttonSelected+1)%_selectedLayout->getNWidgets()+_selectedLayout->getNWidgets())%_selectedLayout->getNWidgets());
                static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseEntered();
            }
            if (InputManager::action(InputAction::menuUp)) {
                _elapsedPress = 0;
                _window->setMouseCursorVisible(false);

                if (_buttonSelected >= 0) static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseLeft();
                _buttonSelected = (((_buttonSelected-1)%_selectedLayout->getNWidgets()+_selectedLayout->getNWidgets())%_selectedLayout->getNWidgets());
                static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseEntered();
            }
            if (InputManager::action(InputAction::menuEnter)) {
                if (_buttonSelected == -1) _buttonSelected = 0;
                static_cast<Button*>(_selectedLayout->at(_buttonSelected))->onClick(sf::Event(),*static_cast<Button*>(_selectedLayout->at(_buttonSelected)));
            }
            float axis = InputManager::action(InputAction::menuMovement);
            if (std::abs(axis) > 0.5) {
                _elapsedPress = 0;
                _window->setMouseCursorVisible(false);
                if (axis < 0) {
                    if (_buttonSelected >= 0) static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseLeft();
                    _buttonSelected = (((_buttonSelected-1)%_selectedLayout->getNWidgets()+_selectedLayout->getNWidgets())%_selectedLayout->getNWidgets());
                    static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseEntered();
                }
                else {
                    if (_buttonSelected >= 0) static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseLeft();
                    _buttonSelected = (((_buttonSelected+1)%_selectedLayout->getNWidgets()+_selectedLayout->getNWidgets())%_selectedLayout->getNWidgets());
                    static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseEntered();
                }
            }
            break;}
        case status::running:
            while (_window->pollEvent(event)) {
                TextBoxManager::processEvent(event);
                if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
                else if (event.type == sf::Event::Resized) {
					resizing();
                }
                else if (event.type == sf::Event::LostFocus) {
                    _focus = false;
                    _elapsedPress = 0;
                    _status = status::onMenu;
                    _selectedLayout = _menuLayout;
                    _buttonSelected = 0;
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E){
                    if(!_player->speaking()) _player->setSpeaking(true);
                    else _player->setSpeaking(false);
                }

            }
            if (InputManager::action(InputAction::pause) && _elapsedPress > 0.3 ) {
                _elapsedPress = 0;
                _status = status::onMenu;
                _selectedLayout = _menuLayout;
                _buttonSelected = 0;
                static_cast<TextButton*>(_selectedLayout->at(_buttonSelected))->onMouseEntered();
            }

            if      (InputManager::action(InputAction::action)) _player->attack();
            if      (InputManager::action(InputAction::up)    || InputManager::action(InputAction::p1movementY) < -0.5) _player->move(directions::up);
            else if (InputManager::action(InputAction::down)  || InputManager::action(InputAction::p1movementY) >  0.5) _player->move(directions::down);
            else if (InputManager::action(InputAction::right) || InputManager::action(InputAction::p1movementX) >  0.5) _player->move(directions::right);
            else if (InputManager::action(InputAction::left)  || InputManager::action(InputAction::p1movementX) < -0.5) _player->move(directions::left);

            if (InputManager::action(InputAction::fairyAction)) {
                sf::Vector2f begin = getRelativeCenter(_fairy->getPosition(), _fairy->getBounds(), FairyShoot::bounds());
                sf::Vector2f end = getRelativeCenter(_player->getPosition(), _player->getBounds(), FairyShoot::bounds());
                _allyWeapons.push_back(new FairyShoot(&_map, begin, end, directions::up));
            }
            // for (int i = 0; i < 32; ++i) if (sf::Joystick::isButtonPressed(0,i)) std::cout << i << std::endl;

            break;
    }

}

void ScenePlayable::initMenu() {
	_menu = Frame(*_window, _viewUI);
	_hud = Frame(*_window, _viewUI);

	_menu.setLayout(_menuLayout);
	_hud.setLayout(_guiLayout);
	_hud.setPosition(0, 0);

	_space->setSize(sf::Vector2f(0, _viewUI.getSize().y*0.7 - _items->getSize().y - _life->getSize().y));
}

void ScenePlayable::resizing() {
	initView(&_view, sf::Vector2i(WINDOWRATIOX, WINDOWRATIOY));
	initView(&_viewUI, sf::Vector2i(UIRATIOX, UIRATIOY));
	centerView(true);
}

void ScenePlayable::setEnemies(std::vector<std::pair<enemyType, sf::Vector2f> > enemies) {
    _enemiesIni = enemies;
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

void ScenePlayable::addProp(Collisionable* prop) {
    _props.push_back(prop);
}

void ScenePlayable::addObject(Object* object) {
    _objects.push_back(object);
}

void ScenePlayable::update(float deltaTime) {
    _elapsedPress += deltaTime;
    if (_status == status::onMenu) {
        
        return;
    }
    _player->update(deltaTime);
    // mousePosition GamePad
    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(*_window));
    float axisX = InputManager::action(InputAction::p2movementX);
    if (std::abs(axisX) > 0.2) {
        mousePosition.x += axisX * (_window->getSize().x/10.f) * deltaTime;
    }
    float axisY = InputManager::action(InputAction::p2movementY);
    if (std::abs(axisY) > 0.2) {
        mousePosition.y += axisY * (_window->getSize().x/10.f) * deltaTime;
    }
    sf::Mouse::setPosition(mousePosition,*_window);

    _fairy->update(deltaTime, sf::Vector2f(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window),_view)));
    _fairy->setCenterPosition(sf::Vector2f(_player->getPosition()));
    for (auto it = _enemies.begin(); it != _enemies.end(); ++it) (*it)->update(deltaTime);
    for (auto it = _enemyWeapons.begin(); it != _enemyWeapons.end(); ++it) (*it)->update(deltaTime);
    for (auto it = _allyWeapons.begin(); it != _allyWeapons.end(); ++it) (*it)->update(deltaTime); 
    for (auto it = _forAllWeapons.begin(); it != _forAllWeapons.end(); ++it) (*it)->update(deltaTime);
    for (auto it = _objects.begin(); it != _objects.end(); ++it) (*it)->update(deltaTime);
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
    {
        sf::IntRect playerBound = _player->getGlobalBound();
        sf::IntRect fairyBounds = _fairy->Collisionable::getGlobalBound();
        //std::cout << fairyBounds.top << " " << fairyBounds.height << std::endl;

        for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
            if (playerBound.intersects((*it)->getGlobalBound())) {
                _player->intersectsWith(*it);
                (*it)->intersectsWith(_player);
            }
            if (fairyBounds.intersects((*it)->getGlobalBound())) {
                _fairy->intersectsWith(*it);
                (*it)->intersectsWith(_fairy);
            }
        }
        for (auto it = _enemyWeapons.begin(); it != _enemyWeapons.end(); ++it) {
            if (playerBound.intersects((*it)->getGlobalBound())) {
                _player->intersectsWith(*it);
                (*it)->intersectsWith(_player);
            }
            if (fairyBounds.intersects((*it)->getGlobalBound())) {
                _fairy->intersectsWith(*it);
                (*it)->intersectsWith(_fairy);
            }
        }
        for (auto it = _forAllWeapons.begin(); it != _forAllWeapons.end(); ++it) {
            if (playerBound.intersects((*it)->getGlobalBound())) {
                _player->intersectsWith(*it);
                (*it)->intersectsWith(_player);
            }
            if (fairyBounds.intersects((*it)->getGlobalBound())) {
                _fairy->intersectsWith(*it);
                (*it)->intersectsWith(_fairy);
            }
        }
        sf::IntRect playerWalkBounds = _player->getGlobalWalkBounds();
        for (auto it = _props.begin(); it != _props.end(); ++it) {
            // here will be like player->colwithprop(gid) prop->collisionwithplayer
            if (playerWalkBounds.intersects((*it)->getGlobalBound())) {
                _player->intersectsWith(*it);
                (*it)->intersectsWith(_player);
            }
        }
        //Colision Player with ally weapons (i.e. fairy shoots must be destroyed)
        for (auto it = _allyWeapons.begin(); it != _allyWeapons.end(); ++it) {
            if (playerWalkBounds.intersects((*it)->getGlobalBound())) {
                _player->intersectsWith(*it);
                (*it)->intersectsWith(_player);
            }
        }
        // Collision between object(rupies, arrows, bombs);
        for (auto it = _objects.begin(); it != _objects.end(); ++it) {
            if (playerBound.intersects((*it)->getGlobalBound())) {
                _player->intersectsWith(*it);
                (*it)->intersectsWith(_player);
            }
        }
    }

    // Collisions between Enemies and things
    for (auto enemyIt = _enemies.begin(); enemyIt != _enemies.end(); ++enemyIt) {
        sf::IntRect bounds = (*enemyIt)->getGlobalBound();
        for (auto it = _allyWeapons.begin(); it != _allyWeapons.end(); ++it) {
            if (bounds.intersects((*it)->getGlobalBound())) {
                (*enemyIt)->intersectsWith(*it);
                (*it)->intersectsWith(*enemyIt);
            }
        }
        for (auto it = _forAllWeapons.begin(); it != _forAllWeapons.end(); ++it) {
            if (bounds.intersects((*it)->getGlobalBound())) {
                (*enemyIt)->intersectsWith(*it);
                (*it)->intersectsWith(*enemyIt);
            }
        }

        sf::IntRect enemyWalkBounds = (*enemyIt)->getGlobalWalkBounds();
        for (auto it = _props.begin(); it != _props.end(); ++it) {
            if (enemyWalkBounds.intersects((*it)->getGlobalBound())) {
                (*enemyIt)->intersectsWith(*it);
                (*it)->intersectsWith(*enemyIt);
            }
        }
        // Collisions between rocks & co
    }

    // Collisions between weapons & props
    { 
        for (auto weaponIt = _enemyWeapons.begin(); weaponIt != _enemyWeapons.end(); ++weaponIt) {
            sf::IntRect bounds = (*weaponIt)->getGlobalBound();
            for (auto it = _props.begin(); it != _props.end(); ++it) {
                if (bounds.intersects((*it)->getGlobalBound())) {
                    (*weaponIt)->intersectsWith(*it);
                    (*it)->intersectsWith(*weaponIt);
                }
            }
        }

        for (auto weaponIt = _allyWeapons.begin(); weaponIt != _allyWeapons.end(); ++weaponIt) {
            sf::IntRect bounds = (*weaponIt)->getGlobalBound();
            for (auto it = _props.begin(); it != _props.end(); ++it) {
                if (bounds.intersects((*it)->getGlobalBound())) {
                    (*weaponIt)->intersectsWith(*it);
                    (*it)->intersectsWith(*weaponIt);
                }
            }
        }

        for (auto weaponIt = _forAllWeapons.begin(); weaponIt != _forAllWeapons.end(); ++weaponIt) {
            sf::IntRect bounds = (*weaponIt)->getGlobalBound();
            for (auto it = _props.begin(); it != _props.end(); ++it) {
                if (bounds.intersects((*it)->getGlobalBound())) {
                    (*weaponIt)->intersectsWith(*it);
                    (*it)->intersectsWith(*weaponIt);
                }
            }
        }
    }

    // Are all the shits alive?
    {
		{
			auto it = _enemies.begin();
			while (it != _enemies.end()) {
				if (!(*it)->isAlive()) {
					delete (*it);
					it = _enemies.erase(it);
				}
				else ++it;
			}
		}
		{
			auto it = _enemyWeapons.begin();
			while (it != _enemyWeapons.end()) {
				if (!(*it)->isAlive()) {
					delete (*it);
					it = _enemyWeapons.erase(it);
				}
				else ++it;
			}
		}
		{
			auto it = _allyWeapons.begin();
			while (it != _allyWeapons.end()) {
				if (!(*it)->isAlive()) {
					delete (*it);
					it = _allyWeapons.erase(it);
				}
				else ++it;
			}
		}
		{
			auto it = _forAllWeapons.begin();
			while (it != _forAllWeapons.end()) {
				if (!(*it)->isAlive()) {
					delete (*it);
					it = _forAllWeapons.erase(it);
				}
				else ++it;
			}
		} 
		{
			auto it = _objects.begin();
			while (it != _objects.end()) {
				if (!(*it)->isAlive()) {
					delete (*it);
					it = _objects.erase(it);
				}
				else ++it;
			}
		}
        // Objects (rupies, shit)
    }

    updateHUD();
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
    for (auto it = _objects.begin(); it != _objects.end(); ++it) collisionables.push_back(*it);
    renderSorted(target, collisionables);
    _map.drawForeground(target);
}

void ScenePlayable::clearMap() {
    for (Enemy* enemy : _enemies) {
        delete enemy;
    }
    _enemies.clear();
    for(Weapon* weapon : _allyWeapons) {
        delete weapon;
    }
	_allyWeapons.clear();
    for(Weapon* weapon : _enemyWeapons) {
        delete weapon;
    }
	_enemyWeapons.clear();
    for(Weapon* weapon : _forAllWeapons) {
        delete weapon;
    }
	_forAllWeapons.clear();
}

void ScenePlayable::initEnemies(sf::Vector2f pos) {
    for (auto pair : _enemiesIni) {
        switch (pair.first) {
            case enemyType::octorok:
                addEnemy(new Octorok(this, &_map, pair.second+pos));
                break;
            case enemyType::penguin:
                addEnemy(new EnemyPenguin(this, &_map, pair.second+pos));
                break;
            default:
                std::cout << "WARNING! Trying to initialice some enemy with a wrong type at scene " << _sceneName << std::endl;
                break;
        }
    }
}

void ScenePlayable::updateHUD() {
    float total = _player->getHp()+_fairy->getHp();
    _player->setHp(total);
    _fairy->setHp(0);
    _life->setMaxHP(_player->getMaxHp());
    _life->setActualHP(total);
    //if( total < 0) kill both

    _qttyKeys->setText(std::to_string(_player->keys()));
    _qttyRupias->setText(std::to_string(_player->rupias()));
}
