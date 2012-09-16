#ifndef POISON_H
#define POISON_H

#include <string>
#include <SFML/Graphics.hpp>
#include "GameObjectClass.h"

class Poison : public GameObjectClass
{
public:
	static bool Init(sf::Image *ImagePointer, sf::Sprite *Player)
    {
		mPlayer = Player;
        mImage = ImagePointer;
		return true;
    }
	Poison();
	Poison( int x, int y );
	void SetPosition( int x, int y ) { mSprite.SetPosition((float)x, (float)y); }
	//void update(sf::RenderWindow &App, const sf::Sprite &player);
	void update();
	//void draw(sf::RenderWindow &App);
	void draw();
	bool alive(){return mAlive;}
private:
    sf::Sprite mSprite; // one per instance
	static sf::Image *mImage;
	static sf::Sprite *mPlayer;
	float mMoveSpeed;
	bool mAlive;
};

#endif //POISON_H
