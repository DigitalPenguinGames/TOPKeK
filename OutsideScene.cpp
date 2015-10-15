#include "OutsideScene.hpp"
#include "Game.hpp"

OutsideScene::OutsideScene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description) :
    ScenePlayable(g,w,sT,name,description)
{

    //std::cout << &(*w) << std::endl;
    _sceneIniCoord = sf::Vector2f(FLT_MAX,FLT_MAX);
}

OutsideScene::~OutsideScene() {

}

void OutsideScene::init(sf::Vector2f sceneIniCoord = sf::Vector2f(0,0)) {
    _player->setMap(&_map);
    if (sceneIniCoord == _sceneIniCoord) return;
    _sceneIniCoord = sceneIniCoord;
    _map.init(_sceneIniCoord);
    initView(sf::Vector2i(WINDOWRATIOX,WINDOWRATIOY));
    _enemies.push_back(new Octorok(this, &_map, sf::Vector2f(70+sceneIniCoord.x,70+sceneIniCoord.y)));
}



void OutsideScene::update(float deltaTime) {
    _player->update(deltaTime);
    _fairy->update(deltaTime, sf::Vector2f(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window),_view)));
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

}

void OutsideScene::render(sf::RenderTarget* target) {
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


    //    _fairy->draw((*_window));
    //_player->draw(_window);
}
