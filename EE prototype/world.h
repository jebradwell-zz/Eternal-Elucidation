#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "map.h"

using std::vector;

class World
{
public:
	World(){}
	vector<Map> Maps;
};

#endif //WORLD_H