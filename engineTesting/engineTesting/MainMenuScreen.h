#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include "ScreenClass.h"

class MainMenuScreen : public ScreenClass
{
public:
	MainMenuScreen();
	virtual int Run( sf::RenderWindow &App );
private:
};

#endif //MAIN_MENU_SCREEN_H