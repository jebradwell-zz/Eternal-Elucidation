#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "ScreenClass.h"

class GameScreen : public ScreenClass
{
	public:
	GameScreen();
	virtual int Run( sf::RenderWindow &App );
private:
};

#endif //GAME_SCREEN_H