#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
	Position( int x = 0, int y = 0){}
	bool operator==(const Position &rhs){
		if( this->x == rhs.x && this->y == rhs.y )
			return true;
		else
			return false;
	}
	bool operator!=(const Position &rhs){ return !( *this == rhs ); }
	int x;
	int y;
};

#endif //POSITION_H