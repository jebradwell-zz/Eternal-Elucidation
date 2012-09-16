#ifndef ELUCIDATE_PALETTE_H
#define ELUCIDATE_PALETTE_H

#include <SFML/Graphics.hpp>
#include "GameObjectClass.h"

class ElucidatePalette : public GameObjectClass
{
public:
	static bool Init(sf::Image *ImagePointer)
    {
        mImage = ImagePointer;
		return true;
    }
	ElucidatePalette();
	ElucidatePalette( int x, int y );
	
	void update();
	void draw();
	bool alive(){return mAlive;}
private:
    sf::Sprite mSprite; // one per instance
	static sf::Image *mImage;
	bool mAlive;
};

#endif ELUCIDATE_PALETTE_H
