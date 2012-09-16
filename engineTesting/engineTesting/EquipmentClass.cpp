#include "EquipmentClass.h"
#include "GameClass.h"

const int RectangleBoarder = 3;
EquipmentClass::EquipmentClass()
{
	int xPosPairs[17][2] = { {1, 31}, {1, 31}, {1, 31}, {1, 31}, {1, 31}, {1, 31}, {32, 63}, {64, 95}, {96, 127}, {128, 159}, {160, 191}, {192, 222}, {192, 222}, {192, 222}, {192, 222}, {192, 222}, {192, 222} };
	int yPosPairs[17][2] = { {64, 95}, {96, 127}, {128, 159}, {160, 191}, {192, 223}, {224, 254}, {224, 254}, {224, 254}, {224, 254}, {224, 254}, {224, 254}, {224, 254}, {192, 223}, {160, 191}, {128, 159}, {96, 127}, {64, 95} };
	
	for(int i = 0; i < 17; i++ )
	{
		this->mXPosPairs[i][0] = xPosPairs[i][0] + RectangleBoarder + (ItemSpriteWidth / 2);
		this->mXPosPairs[i][1] = xPosPairs[i][1] + RectangleBoarder + (ItemSpriteWidth / 2);
		this->mYPosPairs[i][0] = yPosPairs[i][0] + RectangleBoarder + (ItemSpriteHeight / 2);
		this->mYPosPairs[i][1] = yPosPairs[i][1] + RectangleBoarder + (ItemSpriteHeight / 2);

		//set all items pointers to NULL to start
		mItems[i] = NULL;
	}
	
}

void EquipmentClass::draw()
{
	GameClass *GC = Game::getInstance();
	for( int i = 0; i < numberOfEquipment; i++)
	{
		if( mItems[i] != NULL)
		{
			mItems[i]->setPosition(mXPosPairs[i][0] + GC->characterSheet_XPos, mYPosPairs[i][0] + GC->characterSheet_YPos);
			mItems[i]->draw();
		}
	}
}

void EquipmentClass::update()
{
}

Item *EquipmentClass::addEquipment( int EquipmentTypeLocation, Item *item)
{
	//check to see if the item is in fact an Equipment type
	//AND that the location it is being added is the correct 
	//slot for the equipment being placed. i.e. a helmet goes
	//in the head slot.
	Item *tmp = mItems[EquipmentTypeLocation];
	if(item->mType == ItemTypes::Equipment && (EquipmentTypeLocation == item->mEquipmentType || EquipmentTypeLocation >= EquipmentTypes::ElucidationTile))
	{
		mItems[EquipmentTypeLocation] = item;
		return tmp;
	}
	return tmp;
}

//Remove the equipment selected and return a pointer to the equipment item.
Item *EquipmentClass::getEquipment( int EquipmentTypeLocation )
{
	Item *tmp = mItems[EquipmentTypeLocation];
	mItems[EquipmentTypeLocation] = NULL;
	return tmp;
}