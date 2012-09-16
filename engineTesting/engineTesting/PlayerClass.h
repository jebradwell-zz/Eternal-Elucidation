#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "GameObjectClass.h"
#include "Item.h"
#include "EquipmentClass.h"
#include "Singleton.h"


class PlayerClass : public GameObjectClass
{
public:
	static bool Init(sf::Image *ImagePointer)
	{
		mImage = ImagePointer;
		return true;
	}
	PlayerClass();
	PlayerClass(int x, int y);
	void update();
	void draw();
	bool alive(){return mAlive;}
private:
	bool mAlive;
	static sf::Image *mImage;
	sf::Sprite mSprite;
	//std::vector<Item> mEquipment;
	//std::vector<Item> mOrbs;
	//std::vector<Item> mInventory;
};

typedef Singleton<PlayerClass> Player;

#endif //PLAYER_H