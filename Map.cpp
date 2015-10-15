#include "Map.hpp"
#include "ScenePlayable.hpp"

Map::Map(ScenePlayable* scene, std::string description) : _scene(scene) {
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
    
    while(true){ //hohoho im so evil hohoho
        std::string objectGroup;
        des >> objectGroup;
        if("finish" == objectGroup) break; // rekt m8
        else if ("Objects" == objectGroup) {
            // Nosing at ol huhu
            int numberOfProps;
            des >> numberOfProps;
            for (int i = 0; i < numberOfProps; ++i) {
                int x,y,gid;
                des >> gid >> x >> y;
                std::cout << gid << " " << x << " " << y << std::endl;
                _scene->addProp(new Prop(gid,sf::Vector2f(x,y)) );
            }
        }
        else if ("Exits" == objectGroup) {
            int nExists, x, y, nextSceneX, nextSceneY;
            std::string nextScene;
            des >> nExists;
            for (int i = 0; i < nExists; ++i) {
                des >> x >> y >> nextScene >> nextSceneX >> nextSceneY;
                _sceneChangers.push_back(SceneChanger(sf::Vector2f(x,y),nextScene,sf::Vector2f(nextSceneX,nextSceneY)));
            }
        }
        else {
            // I crai evritime
            std::cout << "Broken as fuck :/ We dont have a object group that is called " << objectGroup << std::endl;
            exit(EXIT_FAILURE);
        }
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
        {
            sf::RenderTexture texture;
            texture.create(_premap.size()*TILESIZE, _premap[0].size()*TILESIZE);

            _map = std::vector<std::vector<Tile> >(_premap.size(), std::vector<Tile>(_premap[0].size()));
            for (int j = 0; j < int(_premap[0].size()); ++j){
                for (int i = 0; i < int(_premap.size()); ++i) {
                    sf::Vector2f pos(i*TILESIZE,j*TILESIZE);
                    _map[i][j] = (Tile(_premap[i][j],pos, sceneIniCoord));
                    _map[i][j].drawCollision(&texture);
                }
            }

            texture.display();
            _collisionBackground= texture.getTexture().copyToImage();
            break;
        }
        case sceneTypes::lightedDungeon:
        case sceneTypes::dungeon:
            _background = new Background(_mapIniCoord);
            _collisionBackground = Resources::dungeonCols.copyToImage();
            break;
        default:
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

sf::Vector2f Map::getMaxMovement(sf::Vector2f ini, sf::Vector2f movement, sf::IntRect rect) {
    bool hit = false;
    sf::Vector2f final = ini + movement - _mapIniCoord;

    sf::Vector2f size(getSize().x * TILESIZE,getSize().y * TILESIZE);

    float left = std::max(0.0f,final.x + rect.left);
    float top = std::max(0.0f,final.y + rect.top);

    float width = std::min(left + rect.width,size.x);
    float height = std::min(top + rect.height,size.y);
    

    for (int i = left; i < width ; ++i) {
        for(int j = top; j < height; ++j) {
            sf::Color color = _collisionBackground.getPixel(i,j);
            if (color != sf::Color::White) {
                hit = true;
                return sf::Vector2f(0,0);
            }
        }
    }

    if (hit) return sf::Vector2f(0,0);
    return movement;
}