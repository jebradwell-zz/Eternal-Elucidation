#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <SFML/Graphics.hpp>

class GameObjectClass
{
public:
	static bool Init( sf::RenderWindow *App )
	{
		mApp = App;
		return true;
	}
	GameObjectClass();
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual bool alive() = 0;
	static sf::RenderWindow *mApp;
private:
};

#endif //GAME_OBJECT