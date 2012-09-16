#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <SFML/Graphics.hpp>

#include "Singleton.h"
#include "GameObjectClass.h"
#include "Item.h"

const int numberOfEquipment = 17;
namespace EquipmentTypes
{
enum EquipmentSquares
	{
		Head,
		Shoulders,
		Arms,
		Gloves,
		Legs,
		Boots,
		Ring1,
		MainHand,
		Belt,
		OffHand,
		Ring2,
		ElucidationTile
	};
}

class EquipmentClass : public GameObjectClass
{
public:
	EquipmentClass(); //set the position of the equipment on construction.
	void update();
	void draw();
	bool alive() {return mAlive;}
	//checks the equipmentType location against the item's equipment 
	//type and if they match then it addes the item to the slot.
	Item *addEquipment( int EquipmentTypeLocation, Item *item);
	Item *getEquipment( int EquipmentTypeLocation );
private:
	bool mAlive;
	Item *mItems[numberOfEquipment];
	int mXPosPairs[17][2];
	int mYPosPairs[17][2];
};

typedef Singleton<EquipmentClass> Equipment;

#endif