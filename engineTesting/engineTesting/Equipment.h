#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Singleton.h"
#include "GameObjectClass.h"
#include "Item.h"

const int numberOfEquipment = 17;

class Equipment : public GameObjectClass
{
public:
	static bool Init(sf::Image *ImagePointer)
	{
		mImage = ImagePointer;
		return true;
	}
	Equipment(int x, int y); //set the position of the equipment on construction.
	void update();
	void draw();
	bool alive() {return mAlive;}
	void setPosition( int x, int y );
	void setSubRec(int L, int T, int R, int B);
private:
	bool mAlive;
	sf::Sprite mSprite;
	static sf::Image *mImage;
	Item mItems[numberOfEquipment];
};

typedef Singleton<Equipment> Equipment;

#endif