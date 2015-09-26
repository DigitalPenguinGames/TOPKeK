#include "Map.hpp"

Map::Map(std::string description) {
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


	for (int j = 0; j < int(_premap[0].size()); ++j) {
		for (int i = 0; i < int(_premap.size()); ++i) {
			std::cout << _premap[i][j] << " ";
		}
		std::cout << std::endl;
	}
	


	int nExists, x, y, nextSceneX, nextSceneY;
	std::string nextScene;
	des >> nExists;
	for (int i = 0; i < nExists; ++i) {
		des >> x >> y >> nextScene >> nextSceneX >> nextSceneY;
		std::cout << " " << x << " " << y << " " << nextScene << " " << nextSceneX << " " << nextSceneY;
	}



}

Map::~Map() {
	// for (int i = 0; i < int(_map.size()); ++i) 
	// 	for (int j = 0; j < int(_map[i].size()); ++j) 
	// 		delete &_map[i][j];
}

void Map::init() {
	_map = std::vector<std::vector<Tile> >(_premap.size(), std::vector<Tile>(_premap[0].size()));
	for (int j = 0; j < int(_premap[0].size()); ++j) 
		for (int i = 0; i < int(_premap.size()); ++i) {
			sf::Vector2f pos(i*TILESIZE,j*TILESIZE);
			_map[i][j] = (Tile(_premap[i][j],pos));
		}
	
}

void Map::draw(sf::RenderWindow* w) {
	for (int j = 0; j < int(_map[0].size()); ++j) 
		for (int i = 0; i < int(_map.size()); ++i)
	 		_map[i][j].draw(w);
}