#ifndef TREE_H
#define TREE_H

#include "GameObjectClass.h"

class Tree : public GameObjectClass
{
public:
		static bool Init(sf::Image *ImagePointer, sf::Sprite *Player)
    {
		mPlayer = Player;
        mImage = ImagePointer;
		return true;
    }
	Tree(){}
	Tree( int x, int y );
	void update();
	void draw();
	bool alive(){return mAlive;}
private:
	static sf::Image *mImage;
	static sf::Sprite *mPlayer;
	sf::Sprite mSprite;
	bool mAlive;
};

#endif