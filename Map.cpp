#include "Map.hpp"

Map::Map(std::string description) {
	_mapIniCoord = sf::Vector2f(FLT_MAX,FLT_MAX);
	std::istringstream des(description);
	int typeOfMap, width, height;
	des >> typeOfMap >> width >> height;
	std::cout << typeOfMap << " " << width << " " << height << std::endl;
	_premap = std::vector < std::vector < int > >(width,std::vector<int>(height));
	for (int j = 0; j < int(_premap[0].size()); ++j) {
		for (int i = 0; i < int(_premap.size()); ++i) {
			des >> _premap[i][j];
		}
	}


	// for (int j = 0; j < int(_premap[0].size()); ++j) {
	// 	for (int i = 0; i < int(_premap.size()); ++i) {
	// 		std::cout << _premap[i][j] << " ";
	// 	}
	// 	std::cout << std::endl;
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
	// 	for (int j = 0; j < int(_map[i].size()); ++j) 
	// 		delete &_map[i][j];
}

void Map::init(sf::Vector2f sceneIniCoord) {
	_map = std::vector<std::vector<Tile> >(_premap.size(), std::vector<Tile>(_premap[0].size()));
	for (int j = 0; j < int(_premap[0].size()); ++j) 
		for (int i = 0; i < int(_premap.size()); ++i) {
			sf::Vector2f pos(i*TILESIZE+sceneIniCoord.x,j*TILESIZE+sceneIniCoord.y);
			_map[i][j] = (Tile(_premap[i][j],pos));
		}
	_mapIniCoord = sceneIniCoord;
}

void Map::draw(sf::RenderWindow* w) {
	for (int j = 0; j < int(_map[0].size()); ++j) 
		for (int i = 0; i < int(_map.size()); ++i)
	 		_map[i][j].draw(w);

	//std::cout << "Drawing map from " << _mapIniCoord.x << std::endl;
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
	return sf::Vector2i(_premap.size(),_premap[0].size());
}