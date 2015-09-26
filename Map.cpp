#include "Map.hpp"

Map::Map(std::string description) {
	std::istringstream des(description);
	int typeOfMap, width, height;
	des >> typeOfMap >> width >> height;
	std::cout << typeOfMap << " " << width << " " << height << std::endl;
	premap = std::vector < std::vector < int > >(width,std::vector<int>(height));
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			des >> premap[i][j];
		}
	}


	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			std::cout << premap[i][j] << " ";
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

}

void Map::init() {
	
}