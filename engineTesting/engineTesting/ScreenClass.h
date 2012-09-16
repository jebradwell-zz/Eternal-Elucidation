#ifndef SCREEN_CLASS_H
#define SCREEN_CLASS_H

#include <SFML/Graphics.hpp>

class ScreenClass
{
public:
	virtual int Run (sf::RenderWindow &App) = 0;
private:
};

#endif //SCREEN_CLASS_H