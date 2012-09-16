#ifndef GAME_BULLET_H
#define BULLET_OBJECT_H

#include "GameObject.h"

class GameBullet : public GameObject
{
public:
	CLASS_TYPE(GameBullet);
	DEFAULT_SERIALIZATION;
};

#endif //BULLET_OBJECT_H