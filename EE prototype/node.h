#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "position.h"

enum tile_type
{
	wall,
	moveable,
	start,
	end,
	path
};

class Node
{
public:
	Node( int node_pos_x = 0, int node_pos_y = 0, int tile_type = 0, int s_value = 0, int h_value = 0, int c_value = 0 );
	void setPosition( int x, int y );
	bool operator==(const Node &rhs);
	int tile_type;
	int s_value;
	int h_value;
	int c_value;
	Position pos;
	Node *parent_node;
};

#endif //NODE_H