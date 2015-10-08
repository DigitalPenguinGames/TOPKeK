#include "ScenePlayable.hpp"
#include "Game.hpp"

ScenePlayable::ScenePlayable(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name, std::string description) :
    Scene(g,w,sT,name),
    _map(description),
    _menu(*w)
{

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


/*
    w->draw(_menu);
    w->display();
    while(1);
*/
    //std::cout << "dad:" <<&(*w) << std::endl;

    _status = status::running;
    _fairy = new Fairy();
}

ScenePlayable::~ScenePlayable(){}

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
        float pos1 = c1->getPosition().y+c1->getPosition().x*0.01;
        float pos2 = c2->getPosition().y+c2->getPosition().x*0.01;
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
    sf::Vector2f playerPos = _player->getPositionTransition()+ playerPrediction;
    
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
