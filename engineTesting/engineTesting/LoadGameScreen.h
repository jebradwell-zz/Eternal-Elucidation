#ifndef LOAD_GAME_SCREEN_H
#define LOAD_GAME_SCREEN_H

#include "ScreenClass.h"

class LoadGameScreen : public ScreenClass
{
	public:
	LoadGameScreen();
	virtual int Run( sf::RenderWindow &App );
private:
};

#endif //LOAD_GAME_SCREEN_H