#ifndef INPUT_MODULE_H
#define INPUT_MODULE_H

#include <SFML/Graphics.hpp>
#include "GameClass.h"

typedef struct Directions
{
	unsigned int dir : 4;
	unsigned int extra : 4;
} directions;

//typedef struct KeyStates
//{
//	bool CKey;
//}keyStates;

class InputModule
{
public:
	static bool Init()
	{
		GC = Game::getInstance();
		mApp = GC->App;
		return true;
	}
	InputModule();
	int update();
private:
	float mElapseTime;
	static sf::RenderWindow *mApp;
	static GameClass *GC;
	directions mTest;
};

#endif //INPUT_MODULE_H
