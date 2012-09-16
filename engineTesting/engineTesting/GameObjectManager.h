#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "Singleton.h"
#include "GameObjectClass.h"

typedef enum ObjectIDs
{
	goblin,
	spawner,
	tree,
	bush
}objectIDs;

class GameObjectManager
{
public:
	static void Init()
	{
		mIDPool = 0;
	}
	GameObjectManager(){};
	//returns - a unique Game ID string for the newly created object
	//param - ID of the type of object to be created.
	//int createGameObject( int ID, int spawnID = -1);
	int addGameObject( GameObjectClass *object );
	void update();
private:
	static int mIDPool;
};

typedef Singleton<GameObjectManager> GameOM;

#endif //GAME_OBJECT_MANAGER_H