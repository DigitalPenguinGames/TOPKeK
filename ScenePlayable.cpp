#include "ScenePlayable.hpp"
#include "Game.hpp"

ScenePlayable::ScenePlayable(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description) :
    Scene(g,w,sT,name),
    _map(description) {    
    _status = status::running;
    _fairy = new Fairy();
}

ScenePlayable::~ScenePlayable(){}

sf::Vector2f ScenePlayable::getSceneCoord() {
    return _map.getPtrTile(sf::Vector2i(0,0))->getPosition();
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
        float pos1 = c1->getPosition().y+c1->getPosition().x*0.01;
        float pos2 = c2->getPosition().y+c2->getPosition().x*0.01;
        return pos1 > pos2;
    }
};

void ScenePlayable::renderSorted(std::vector<Collisionable*>& cols) {
    std::priority_queue<Collisionable*, std::vector<Collisionable*>, CollisionPositionCompare> thingsToDraw;
    for (int i = 0; i < cols.size(); ++i) thingsToDraw.push(cols[i]);

    while (!thingsToDraw.empty()) {
        thingsToDraw.top()->draw(_window);
        thingsToDraw.pop();
    }
}


void ScenePlayable::display() {
    _window->clear();
    switch(_status){
        case status::onMenu:
            // set the PauseMenú view
            // render pause menú
            //break;
        case status::running:
            _window->setView(_view);
            render();
            _window->setView(_window->getDefaultView());
            break;


        default:
            break;
    }
    _window->display();
}
