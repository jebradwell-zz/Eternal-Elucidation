#include "node.h"

Node::Node( int node_pos_x, int node_pos_y, int tile_type, int s_value, int h_value, int c_value ) : tile_type(tile_type), s_value(s_value), h_value(h_value), c_value(c_value)
{
	setPosition( node_pos_x, node_pos_x );
}
void Node::setPosition( int x, int y )
{
	this->pos.x = 0;
	this->pos.y = 0;
}

bool Node::operator ==(const Node &rhs)
{
	if( this->pos.x == rhs.pos.x && this->pos.y == rhs.pos.y )
		return true;
	else
		return false;
}