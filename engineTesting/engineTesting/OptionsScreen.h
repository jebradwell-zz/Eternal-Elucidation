#ifndef OPTIONS_SCREEN_H
#define OPTIONS_SCREEN_H

#include "ScreenClass.h"
namespace NSOptions
{
	enum Options
	{
		screenSize,
		fullScreen,
		inputType,
		difficulty
	};
};

class OptionsScreen : public ScreenClass
{
public:
	OptionsScreen();
	virtual int Run( sf::RenderWindow &App );
private:
};

#endif //OPTIONS_SCREEN_H
