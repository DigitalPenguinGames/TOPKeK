#ifndef __MAP_HPP__
#define __MAP_HPP__

#include "utils.hpp"

class Map {
public:
	Map(std::string description);
	~Map();
	void init();

private:
	std::vector<std::vector<int> > premap;
};

#endif