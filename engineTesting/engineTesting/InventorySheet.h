#ifndef INVENTORY_SHEET_H
#define INVENTORY_SHEET_H

#include <SFML/Graphics.hpp>
#include "GameObjectClass.h"
#include "Item.h"

class InventorySheet : public GameObjectClass
{
public:
	static bool Init(sf::Image *ImagePointer)
	{
		mImage = ImagePointer;
		return true;
	}
	InventorySheet(int x, int y);
	void update();
	void draw();
	bool alive(){return mAlive;}
private:
	void updateInputs();
	bool mAlive;
	bool mDraw;
	bool mIKeyState;
	bool mLeftMouseState;
	int mItemXLocation;
	int mItemYLocation;
	int mSpriteXpos;
	int mSpriteYpos;
	int mSelectedRectangle;
	sf::Shape mRectangle;
	int mMouseX;
	int mMouseY;
	sf::Sprite mSprite;
	static sf::Image *mImage;
	
};

#endif //INVENTORY_SHEET_H