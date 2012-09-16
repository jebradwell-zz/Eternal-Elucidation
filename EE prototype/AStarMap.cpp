#include "AStarMap.h"

AStarMap::AStarMap()
{
	init_map( DEFAULT_MAP_ROWS, DEFAULT_MAP_COLUMNS );
}
AStarMap::AStarMap( int rows, int columns ) 
{
	init_map(rows, columns);
}
void AStarMap::init_map( int rows, int columns )
{
	this->rows = rows;
	this->columns = columns;
		map = new Node*[columns];
	for( int i = 0; i < columns; i++)
	{
		map[i] = new Node[rows];
	}
	for( int j = 0; j < columns; j++ )
	{
		for( int i = 0; i < rows; i++ )
		{
			map[j][i].pos.x = i;
			map[j][i].pos.y = j;
		}
	}
}

AStarMap &AStarMap::operator =( const AStarMap &rhs )
{
	if( this->columns == rhs.columns && this->rows == rhs.rows )
	{
		for( int j = 0; j < this->columns; j++ )
		{
			for( int i = 0; i < this->rows; i++ )
			{
				map[j][i] = rhs.map[j][i];
			}
		}
	}
	else
	{
		std::cout << "Maps are not equal: [Rows][Columbs" << std::endl;
		std::cout << "Left  hand side = [" << this->rows << "][" << this->columns << "]" << std::endl;
		std::cout << "Right hand side = [" << rhs.rows << "][" << rhs.columns << "]" << std::endl;
	}
	return *this;
}
AStarMap::AStarMap( const AStarMap &copy )
{
	this->rows = copy.rows;
	this->columns = copy.columns;
	map = new Node*[copy.columns];
	for( int i = 0; i < copy.columns; i++)
	{
		map[i] = new Node[copy.rows];
	}
	*this = copy;
}

AStarMap::~AStarMap()
{
	for( int i = 0; i < columns; i++ )
	{
		delete[] map[i];
	}
	delete[] map;
}