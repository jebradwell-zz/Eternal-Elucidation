#ifndef ITEM_H
#define ITEM_H

#include "GameObjectClass.h"
#include <iostream>

//These need to be changed to 32 X 32 eventually
const int ItemSpriteWidth = 27;
const int ItemSpriteHeight = 28;

namespace ItemTypes
{
	enum itemType
	{
		Orb,
		Equipment,
		KeyItem,
		QuestItem
	};
}

class Item : public GameObjectClass
{
public:
	Item();
	void setPosition(int x, int y);
	void setSubRec( int L, int T, int R, int B);
	void setImage( sf::Image &Image);
	void update();
	void draw();
	bool alive() {return mAlive;}
	bool isSet() {return mImageSet;}
	int mType; //orb,  equipment, key item, quest item, etc.
	int mEquipmentType; //Head, Shoulders, Arms, Legs, Boots, weapons, elucidate tiles etc.
	int mCurrentAmount;
	int mMaxAmount;
	std::string mName;
	std::string mDescription;
private:
	bool mAlive;
	bool mImageSet;
	//item sizes are 27 X 28... NOTE NEED TO CHANGE THIS TO 32 X 32 eventually.
	sf::Sprite mSprite;
};

#endif //ITEM_H