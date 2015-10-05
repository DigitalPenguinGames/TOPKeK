#include "Game.hpp"

Game::Game() : _window(sf::VideoMode::getDesktopMode(),"TOPKeK", sf::Style::Close | sf::Style::Resize) {
    //_window.setFramerateLimit(FRAMERATE);
    Resources::load();
    _currentScene = nullptr;
    _lastScene = nullptr;
}

Game::~Game() {
    for (auto it = _scenes.begin(); it != _scenes.end(); ++it) {
        delete it->second;
    }
}

void Game::start() {
    loadScenes();
    changeScene(new SceneChanger(sf::Vector2f(0,0),"ini",sf::Vector2f(0,0)));

    OutsideScene* aux = dynamic_cast<OutsideScene*>((*_scenes.find("ini")).second);
    aux->setPlayer(new Player());

    while (_currentScene != nullptr) {
        _currentScene->run();
    }

    exit(0);
}


void Game::changeScene(SceneChanger* sC) { // This will be called by any scene when something trigers to change to anothe scene
    std::string sceneName = sC->_nextScene;
    sf::Vector2f sceneIniCoord(0,0);
    if (_currentScene != nullptr) {
        _lastScene = _currentScene;
        _currentScene->killScene();
    }
    auto it = _scenes.find(sceneName);
    if (it == _scenes.end()) {
        std::cout << "The selected scene does not exist: " << sceneName << std::endl;
        exit(EXIT_FAILURE);
    }
    Scene* aux = (*it).second;
    
    std::cout << "Changing to scene " << sceneName << std::endl;

    // Animations
    _currentScene = aux;
    if (_lastScene != nullptr) {
        std::cout << _lastScene->getType() << " " << _currentScene->getType() << std::endl;
        if (_lastScene->getType() == _currentScene->getType()) {
            if (_currentScene->getType() == sceneTypes::outside || _currentScene->getType() == sceneTypes::dungeon) {
                if (sC == nullptr) {std::cout << "ERROR: Changing between two outisde scenes without SceneChanger"<< std::endl;exit(EXIT_FAILURE);}
                
                ScenePlayable* lastScene = dynamic_cast<ScenePlayable*>(_lastScene);
                ScenePlayable* currentScene = dynamic_cast<ScenePlayable*>(_currentScene);

                sf::Vector2f offset;
                directions dir = sC->getChangeDirection();
                switch (dir) {
                    case directions::left:
                        offset.y = TILESIZE * (sC->_pos.y-sC->_nextScenePos.y);
                        offset.x = -currentScene->getMapSize().x*TILESIZE;
                        break;
                    case directions::right:
                        offset.y = TILESIZE * (sC->_pos.y-sC->_nextScenePos.y);
                        offset.x = lastScene->getMapSize().x*TILESIZE;
                        break;
                    case directions::up:
                        offset.x = TILESIZE * (sC->_pos.x-sC->_nextScenePos.x);
                        offset.y = -currentScene->getMapSize().y*TILESIZE;
                        break;
                    case directions::down:
                        offset.x = TILESIZE * (sC->_pos.x-sC->_nextScenePos.x);
                        offset.y = lastScene->getMapSize().y*TILESIZE;
                        break;
                    default:
                        break;
                }

                sceneIniCoord = lastScene->getSceneCoord()+offset;

                //std::cout << "offset: " << offset.x << " " << offset.y << " sceneIniCoord " << sceneIniCoord.x << " " << sceneIniCoord.y << std::endl;
                // std::cout << lastScene->getSceneCoord().x << " " << lastScene->getSceneCoord().y << std::endl;

                _currentScene->init(sceneIniCoord);
                currentScene->setPlayer(lastScene->getPlayer());
                

                // Transition animation:
                sf::View* view = lastScene->getPtrView();
                sf::Vector2f lastViewCenter = view->getCenter();
                //std::cout << view->getCenter().x << " " << view->getCenter().y << std::endl;

                sf::Clock clock;
                sf::Time deltaTime;
                float count=0.f, timer = 1.5f;
                // speed
                sf::Vector2f speed(offset.x/timer,offset.y/timer);
                // zoom
                //float maxzoom = 1.01, originalZoom = 1, speedZoom = (maxzoom - originalZoom)/(timer*2); // cambiar el speed

                //std::cout << "speed: " << speed.x << " " << speed.y << std::endl;

                Player* player = currentScene->getPlayer();

                while (count < timer) {
                    deltaTime = clock.restart();
                    count += deltaTime.asSeconds();
                    view->move(speed*deltaTime.asSeconds());

                    // Moving the player.
                    if (count > timer*(3.5f/4.f)) {
                        player->move(dir);
                        player->update(deltaTime.asSeconds());
                    }

                    // if (count < timer/2.f) view->zoom(1-speedZoom);
                    // else view->zoom(1.f/(1-speedZoom));

                    _window.setView(*view);
                    _window.clear();
                    lastScene->render();
                    currentScene->render();
                    _window.setView(_window.getDefaultView());
                    _window.display();

                }
                
                view->setCenter(lastViewCenter+offset); // Put the center of the camera in his position (like move(speed*(timer-count)))

                _currentScene->_view = *view;
                


                return;
            }
        // 
        }
        else if (_lastScene->getType() == sceneTypes::outside || sceneTypes::dungeon == _currentScene->getType()) {
            ScenePlayable* lastScene = dynamic_cast<ScenePlayable*>(_lastScene);
            ScenePlayable* currentScene = dynamic_cast<ScenePlayable*>(_currentScene);
            currentScene->setPlayer(lastScene->getPlayer());
            
        }
    }    
    _currentScene->init();    
}


void Game::loadScenes() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (SCENEPATH)) != NULL) {
      while ((ent = readdir(dir)) != NULL) {
          std::string aux = ent->d_name;
          if (aux.find(SCENEEXTENSION) != std::string::npos) {
            loadScene(aux);
        }
      }
      closedir (dir);
    } else {
      perror ("Could not open directory");
      exit(EXIT_FAILURE);
    }
}

void Game::loadScene(std::string sceneName) {
    std::cout << sceneName.substr(0,sceneName.length()-sizeof(SCENEEXTENSION)+1) << std::endl;

    std::ifstream t(SCENEPATH + sceneName);
    std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

    std::istringstream description(str);

    std::string sceneType;
    description >> sceneType;
    Scene* aux;
    switch(myStoi(sceneType)) {
        case sceneTypes::outside:
            aux = new OutsideScene(this,&_window,sceneTypes::outside, sceneName, str);
            break;
        case sceneTypes::dungeon:
            aux = new DungeonScene(this,&_window,sceneTypes::dungeon, sceneName, str);
            break;
    }
    
    _scenes.insert(std::make_pair(sceneName.substr(0,sceneName.length()-sizeof(SCENEEXTENSION)+1),aux));
}
