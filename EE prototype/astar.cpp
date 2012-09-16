#include "astar.h"

Astar::Astar(AStarMap *map, int h_type)
{
	this->map = map;
	this->heuristic = h_type;
}

void Astar::calculate_h_value(Node *cur_node)
{
	int xdist = abs(cur_node->pos.x - this->end.x);
	int ydist = abs(cur_node->pos.y - this->end.y);
	if( heuristic == heuristic_type::manhattan_distance )
		cur_node->h_value = xdist + ydist;
	if( heuristic == heuristic_type::eigen_distance )
		cur_node->h_value = (int)sqrt( pow( (float)xdist, 2 ) + pow( (float)ydist, 2 ) );
}

void Astar::calculate_s_value(Node *cur_node)
{
	int cost = 0;
	Node *tmp = cur_node;
	while( tmp->tile_type != tile_type::start )
	{
		cost++;
		tmp = tmp->parent_node;
	}
	cur_node->s_value = cost;
}

void Astar::calculate_c_value( Node *cur_node )
{
	cur_node->c_value = cur_node->s_value + cur_node->h_value;
}

void Astar::calculate_cost( Node* node_to_calculate )
{
	node_to_calculate->parent_node = this->current_node;
	calculate_h_value( node_to_calculate );
	calculate_s_value( node_to_calculate );
	calculate_c_value( node_to_calculate );
}

vector<Node *> Astar::find_path(Position start_pos, Position end_pos)
{
	if( this->start.x >= 0 && this->start.y >= 0 )
	{
	//Make sure to reset the start and end node to moveable again.
	Node *rest_node;
	rest_node = find_node( this->start );
	rest_node->tile_type = tile_type::moveable;
	}

	if( this->end.x >= 0 && this->end.y >= 0 )
	{
	Node *rest_node;
	rest_node = find_node( this->end );
	rest_node->tile_type = tile_type::moveable;
	}

	
	//Set the start and end position passed to this function 
	//to the object's start and end member variables
	this->start = start_pos;
	this->end = end_pos;

	this->current_node = find_node( this->start );
	this->current_node->tile_type = tile_type::start;
	

	this->goal_node = find_node( this->end );
	this->goal_node->tile_type = tile_type::end;

	calculate_cost( this->current_node );

	this->openlist.push_back( this->current_node );
	while( !this->openlist.empty() )
	{
		this->current_node = get_lowset_cost_node();
		if( *this->current_node == *goal_node )
		{
			return track_back_path( this->current_node );
		}
		else
		{
			move_node_to_closelist( this->current_node );
			examine_adjacent_nodes( this->current_node );
		}
	}
	//if we have reached this point then there was no path
	//that could be taken to get to the end node. so we 
	//return a empty vector for the user to check against.
	vector<Node *> no_path;
	return no_path;
}

vector<Node *> Astar::find_path(int start_x, int start_y, int end_x, int end_y)
{
	Position tmp_start;
	Position tmp_end;
	tmp_start.x = start_x;
	tmp_start.y = start_y;
	tmp_end.x = end_x;
	tmp_end.y = end_y;
	return find_path(tmp_start, tmp_end);
}

Node *Astar::find_node(int x, int y)
{
	return &this->map->map[y][x];
}

Node *Astar::find_node(Position node_position)
{

	return &this->map->map[node_position.y][node_position.x];
}

void Astar::move_node_to_closelist(Node *cur_node)
{
	//find the current node in the openlist and erase/remove it
	for( unsigned int i = 0; i < this->openlist.size(); i++ )
	{
		if( *cur_node == *this->openlist[i] )
			this->openlist.erase(openlist.begin() + i);
	}
	//place the current node into the closelist
	closelist.push_back(current_node);
}

//calculate cost and move to open list all 8 adjacent nodes
//which are not on the openlist or close list and are moveable
//we check the edges and if we are on the edge of the map we 
//do NOT look at that tile. Looking at that tile would cause
//an out of index range error.
void Astar::examine_adjacent_nodes(Node *cur_node)
{
	//check the right tile
	if( cur_node->pos.x < this->map->rows - 1 )
	{
		add_to_openlist( find_node(cur_node->pos.x + 1, cur_node->pos.y ) );
	}
	//check the left tile
	if( cur_node->pos.x > 0 )
	{
		add_to_openlist( find_node(cur_node->pos.x - 1, cur_node->pos.y ) );
	}
	//check the bottom tile
	if( cur_node->pos.y < this->map->columns - 1 )
	{
		add_to_openlist( find_node(cur_node->pos.x, cur_node->pos.y + 1 ) );
	}
	//check the top tile
	if( cur_node->pos.y > 0 )
	{
		add_to_openlist( find_node(cur_node->pos.x, cur_node->pos.y - 1 ) );
	}
	//check the top left tile
	if( cur_node->pos.x > 0 && cur_node->pos.y > 0 )
	{
		add_to_openlist( find_node(cur_node->pos.x - 1, cur_node->pos.y - 1 ) );
	}
	//check the top right 
	if( cur_node->pos.x < this->map->rows - 1 && cur_node->pos.y > 0 )
	{
		add_to_openlist( find_node(cur_node->pos.x + 1, cur_node->pos.y - 1 ) );
	}
	//check the bottom right
	if( cur_node->pos.x < this->map->rows - 1 && cur_node->pos.y < this->map->columns - 1 )
	{
		add_to_openlist( find_node(cur_node->pos.x + 1, cur_node->pos.y + 1 ) );
	}
	//check the bottom left
	if( cur_node->pos.x > 0 && cur_node->pos.y < this->map->columns - 1 )
	{
		add_to_openlist( find_node(cur_node->pos.x - 1, cur_node->pos.y + 1 ) );
	}
}

bool Astar::in_openlist(Node *node_to_check)
{
	for( unsigned int i = 0; i < this->openlist.size(); i++ )
	{
		if( *node_to_check == *this->openlist[i] )
			return true;
	}
	return false;
}

bool Astar::in_closelist(Node *node_to_check)
{
	for( unsigned int i = 0; i < this->closelist.size(); i++ )
	{
		if( *node_to_check == *this->closelist[i] )
			return true;
	}
	return false;
}

bool Astar::is_moveable( Node *node_to_check )
{
	if( node_to_check->tile_type != tile_type::wall )
		return true;
	else
		return false;
}

void Astar::add_to_openlist(Node *node_to_check)
{
	if( !in_openlist( node_to_check ) )
		if( !in_closelist( node_to_check ) )
			if( is_moveable( node_to_check ) )
			{
				calculate_cost( node_to_check );
				openlist.push_back( node_to_check );
			}
}

Node *Astar::get_lowset_cost_node()
{
	Node *tmp = openlist[0];
	for( unsigned int i = 0; i < this->openlist.size(); i++ )
	{
		if( tmp->c_value > this->openlist[i]->c_value )
		{
			tmp = this->openlist[i];
		}
	}
	return tmp;
}

vector<Node *> Astar::track_back_path(Node *end_node_found)
{
	Node *tmp = end_node_found;
	vector<Node *> path;
	while( tmp->tile_type != tile_type::start )
	{
		path.push_back( tmp );
		tmp = tmp->parent_node;
	}
	path.push_back(tmp);
	return path;
}