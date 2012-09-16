#include "OrbClass.h"
#include "GameClass.h"

const int RectangleBoarder = 3;
OrbClass::OrbClass()
{
	int circleXYPos[12][2] = { {112, 84}, {142, 92}, {164, 114}, {172, 144}, {164, 174}, {142, 196}, {112, 204}, {82, 196}, {60, 174}, {52, 144}, {60, 114}, {82, 92} };
	//there are 12 circles thus iterate 12 times to
	//copy them all over.
	for( int i = 0; i < 12; i++ )
	{
		mCircleXYPos[i][0] = circleXYPos[i][0];
		mCircleXYPos[i][1] = circleXYPos[i][1];
		mItems[i] = NULL;
	}
}

void OrbClass::draw()
{
	GameClass *GC = Game::getInstance();
	for( int i = 0; i < numberOfOrbs; i++)
	{
		if( mItems[i] != NULL)
		{
			mItems[i]->setPosition(mCircleXYPos[i][0] + GC->characterSheet_XPos, mCircleXYPos[i][1] + GC->characterSheet_YPos);
			mItems[i]->draw();
		}
	}
}

void OrbClass::update()
{
}

Item *OrbClass::addOrb( int OrbLocation, Item *item)
{
	//check to see if the item is in fact an Orb type
	Item *tmp = mItems[OrbLocation];
	if(item->mType == ItemTypes::Orb)
	{
		mItems[OrbLocation] = item;
		return tmp;
	}
	return tmp;
}

//Remove the orb selected and return a pointer to the orb item.
Item *OrbClass::grabOrb( int OrbLocation )
{
	Item *tmp = mItems[OrbLocation];
	mItems[OrbLocation] = NULL;
	return tmp;
}

Item *OrbClass::getOrb( int OrbLocation )
{
	return mItems[OrbLocation];
}