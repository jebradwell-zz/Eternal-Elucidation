#ifndef INVENTORY_CLASS_H
#define INVENTORY_CLASS_H

#include <SFML/Graphics.hpp>

#include "Singleton.h"
#include "GameObjectClass.h"
#include "Item.h"

const int numberOfInventory = 42;

class InventoryClass : public GameObjectClass
{
public:
	InventoryClass();
	void update();
	void draw();
	bool alive() {return mAlive;}
	Item *addItem( int InventoryLocation, Item *item);
	Item *getItem( int InventoryLocation );
private:
	bool mAlive;
	Item *mItems[numberOfInventory];
};

typedef Singleton<InventoryClass> Inventory;

#endif //INVENTORY_CLASS_H