#include "InventoryClass.h"
#include "GameClass.h"

InventoryClass::InventoryClass()
{
	for( int i = 0; i < numberOfInventory; i++)
		mItems[i] = NULL;
}

void InventoryClass::update()
{
}

void InventoryClass::draw()
{
	GameClass *GC = Game::getInstance();
	int j = 0;
	for(int i = 0; i < numberOfInventory; i++)
	{
		if( i != 0 && (i % 6) == 0 )
			j++;
		int x = ((i % 6) * 37) + 4;
		int y = (j * 37) + 36;
		
		if( mItems[i] != NULL)
		{
			x += GC->inventorySheet_XPos + (ItemSpriteWidth / 2);
			y += GC->inventorySheet_YPos + (ItemSpriteHeight / 2);
			mItems[i]->setPosition( x, y);
			mItems[i]->draw();
		}
	}
}

Item *InventoryClass::addItem( int InventoryLocation, Item *item)
{
	//Set item in the inventory and return the item that was 
	//in the selected location. A NULL Item pointer is returned
	//if there is no current item in the selected location.
	Item *tmp = mItems[InventoryLocation];
	mItems[InventoryLocation] = item;
	return tmp;
}

//Remove the selected item and return a pointer to the selected item.
Item *InventoryClass::getItem( int InventoryLocation )
{
	Item *tmp = mItems[InventoryLocation];
	mItems[InventoryLocation] = NULL;
	return tmp;
}