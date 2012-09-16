#include "PlayerClass.h"

PlayerClass::PlayerClass()
{
}
void PlayerClass::update()
{
}

void PlayerClass::draw()
{
	mApp->Draw(mSprite);
	//for( int i = 0; i < mEquipment.size(); i++)
	//{
	//	mEquipment[i].draw();
	//	mOrbs[i].draw();
	//	mInventory[i].draw();
	//}
}