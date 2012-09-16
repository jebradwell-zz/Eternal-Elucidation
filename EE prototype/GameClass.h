#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include "Singleton.h"

class GameClass
{
public:
	//PUBLIC FUNCTIONS/API
	GameClass(){}
	//added 'return *this;' so gcc doesn't give us warnings -Ron
	GameClass( GameClass const &copy){}
	GameClass &operator = (GameClass const &rhs){return *this;}
	~GameClass(){}
};

typedef Singleton<GameClass> GC;


#endif //GAME_CLASS_H