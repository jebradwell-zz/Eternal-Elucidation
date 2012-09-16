#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <vector>
#include <math.h>
#pragma warning(disable:4482)
#include "AStarMap.h"

using std::vector;

enum heuristic_type
{
	manhattan_distance,
	eigen_distance
};

class Astar
{
public:
	Astar( AStarMap *map, int h_type = 0);
	vector<Node *> find_path( Position start, Position end );
	vector<Node *> find_path( int start_x, int start_y, int end_x, int end_y );


private:
	void calculate_h_value( Node *cur_node );
	void calculate_s_value( Node *cur_node );
	void calculate_c_value( Node *cur_node );
	void calculate_cost( Node *node_to_calculate );
	void move_node_to_closelist( Node *cur_node );
	void examine_adjacent_nodes( Node *cur_node );
	bool in_openlist( Node *node_to_check );
	bool in_closelist( Node *node_to_check );
	bool is_moveable( Node *node_to_check );
	Node *find_node( Position node_position );
	Node *find_node( int x, int y );
	void add_to_openlist( Node *node_to_check );
	Node *get_lowset_cost_node();
	vector<Node *> track_back_path( Node *end_node_found );

	int heuristic;
	AStarMap *map;
	Node *current_node;
	Node *goal_node;
	Position start;
	Position end;
	vector<Node*> openlist;
	vector<Node*> closelist;
};

#endif //FUNCTIONS_H