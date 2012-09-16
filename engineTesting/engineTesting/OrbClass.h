#ifndef ORB_H
#define ORB_H

#include <SFML/Graphics.hpp>

#include "Singleton.h"
#include "GameObjectClass.h"
#include "Item.h"

const int numberOfOrbs = 12;

class OrbClass : public GameObjectClass
{
public:
	OrbClass(); //set the position of the equipment on construction.
	void update();
	void draw();
	bool alive() {return mAlive;}
	//checks the equipmentType location against the item's equipment 
	//type and if they match then it addes the item to the slot.
	Item *addOrb( int OrbLocation, Item *item);
	//getorb returns a pointer to the orb at OrbLocation from the mItems pointer array
	//leaving the mItems array in tack.
	Item *getOrb( int OrbLocation );
	//grabOrb returns a pointer to the orb at OrbLocation passed AND removes the orb from the 
	//mItems pointer array by setting the grabed orb pointer to NULL
	Item *grabOrb( int OrbLocation );
private:
	bool mAlive;
	Item *mItems[numberOfOrbs];
	int mCircleXYPos[12][2];
};

typedef Singleton<OrbClass> Orbs;

#endif //ORB_H