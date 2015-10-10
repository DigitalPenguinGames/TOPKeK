#include "Map.hpp"

Map::Map(std::string description) {
    _mapIniCoord = sf::Vector2f(FLT_MAX,FLT_MAX);
    std::istringstream des(description);
    int width, height;
    des >> _mapType;
    switch (_mapType) {
        case sceneTypes::outside: // outside
            des >> width >> height;
            std::cout << _mapType << " " << width << " " << height << std::endl;
            _premap = std::vector < std::vector < int > >(width,std::vector<int>(height));
            for (int j = 0; j < int(_premap[0].size()); ++j) {
                for (int i = 0; i < int(_premap.size()); ++i) {
                    des >> _premap[i][j];
                }
            }
            break;
        case sceneTypes::dungeon: // dungeon
            std::cout << "dungone " << std::endl;
            break;
    } 


    // for (int j = 0; j < int(_premap[0].size()); ++j) {
    //     for (int i = 0; i < int(_premap.size()); ++i) {
    //         std::cout << _premap[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    


    int nExists, x, y, nextSceneX, nextSceneY;
    std::string nextScene;
    des >> nExists;
    for (int i = 0; i < nExists; ++i) {
        des >> x >> y >> nextScene >> nextSceneX >> nextSceneY;
        //std::cout << " " << x << " " << y << " " << nextScene << " " << nextSceneX << " " << nextSceneY;
        _sceneChangers.push_back(SceneChanger(sf::Vector2f(x,y),nextScene,sf::Vector2f(nextSceneX,nextSceneY)));
    }



}

Map::~Map() {
    // for (int i = 0; i < int(_map.size()); ++i) 
    //     for (int j = 0; j < int(_map[i].size()); ++j) 
    //         delete &_map[i][j];
}

void Map::init(sf::Vector2f sceneIniCoord) {
    _mapIniCoord = sceneIniCoord;
    switch (_mapType) {
        case sceneTypes::outside:
            _map = std::vector<std::vector<Tile> >(_premap.size(), std::vector<Tile>(_premap[0].size()));
            for (int j = 0; j < int(_premap[0].size()); ++j) 
                for (int i = 0; i < int(_premap.size()); ++i) {
                    sf::Vector2f pos(i*TILESIZE+sceneIniCoord.x,j*TILESIZE+sceneIniCoord.y);
                    _map[i][j] = (Tile(_premap[i][j],pos));
                }
            break;
        case sceneTypes::lightedDungeon:
        case sceneTypes::dungeon:
            _background = new Background(_mapIniCoord);
            break;
    }
    
}

void Map::draw(sf::RenderTarget* w) {
    switch (_mapType) {
        case sceneTypes::outside:
            for (int j = 0; j < int(_map[0].size()); ++j) 
                for (int i = 0; i < int(_map.size()); ++i)
                     _map[i][j].draw(w);
            break;
        case sceneTypes::lightedDungeon:
        case sceneTypes::dungeon:
            _background->draw(w);
            break;
    }

    //std::cout << "Drawing map from " << _mapIniCoord.x << " " << int(_map[0].size()) << " " << int(_map.size()) << std::endl;
}

std::pair<bool,SceneChanger*> Map::playerInsideExit(sf::Vector2f pos) {
    for (int i = 0; i < int(_sceneChangers.size());++i) {
        if (_sceneChangers[i].getRect(_mapIniCoord).contains(pos)) {
            return std::pair<bool,SceneChanger*>(true,&_sceneChangers[i]);
        }
    }
    return std::pair<bool,SceneChanger*>(false,nullptr);
}

Tile* Map::getPtrTile(sf::Vector2i pos) {
    return &_map[pos.x][pos.y];
}

sf::Vector2i Map::getSize() {
    switch (_mapType) {
        case sceneTypes::dungeon:
        case sceneTypes::lightedDungeon:
            return sf::Vector2i(16,11); // Full Hardcoded
        case sceneTypes::outside:
            return sf::Vector2i(_premap.size(),_premap[0].size());    
    }
    return sf::Vector2i(0,0); // This will not be never called
}


sf::Vector2f Map::getSceneCoord() {
    return _mapIniCoord;
}