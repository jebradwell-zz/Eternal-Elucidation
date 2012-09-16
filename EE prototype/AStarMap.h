#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "node.h"

#define DEFAULT_MAP_ROWS 8
#define DEFAULT_MAP_COLUMNS 8

class AStarMap
{
public:
	AStarMap();
	AStarMap( int rows, int columns);
	AStarMap( const AStarMap &copy );
	AStarMap &operator =( const AStarMap &rhs );
	~AStarMap();
	Node **map;
	int rows;
	int columns;
private:
	void init_map( int rows, int columns );

};

#endif //MAP_H