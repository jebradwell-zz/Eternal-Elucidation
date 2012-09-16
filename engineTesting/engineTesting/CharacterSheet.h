#ifndef CHARACTER_SHEET_H
#define CHARACTER_SHEET_H

#include <SFML/Graphics.hpp>
#include "GameObjectClass.h"
#include "Item.h"

class CharacterSheet : public GameObjectClass
{
public:
	static bool Init(sf::Image *ImagePointer)
	{
		mImage = ImagePointer;
		return true;
	}
	CharacterSheet(int x, int y);
	void update();
	void update(bool test);
	void draw();
	bool alive(){return mAlive;}
	void alive(bool set){ mAlive = set;}
private:
	void updateInputs();
	bool mAlive;
	bool mDraw;
	bool mCKeyState;
	bool mLeftMouseState;
	int mMouseX;
	int mMouseY;
	int mSpriteXpos;
	int mSpriteYpos;
	int mXPosPairs[17][2];
	int mYPosPairs[17][2];
	int mCircleXYPos[12][2];
	int mSelectedRectangle;
	int mSelectedCircle;
	float mRadius;
	sf::Shape mRectangle;
	sf::Shape mCircle;
	sf::Sprite mSprite;
	static sf::Image *mImage;
	
};

#endif