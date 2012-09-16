#include "GameObjectManager.h"
#include "GameClass.h"

int GameObjectManager::mIDPool = 1;

//int GameObjectManager::createGameObject( int ID, int spawnID )
//{
//	GameClass *GC = Game::getInstance();
//	switch( ID )
//	{
//	case objectIDs::goblin:
//		GC->mGameObjects.insert( std::pair<int, GameObject>( mIDPool,  Goblin()) );
//		break;
//	case objectIDs::spawner:
//		switch( spawnID )
//		{
//		case objectIDs::goblin:
//			GC->mGameObjects.insert( std::pair<int, GameObject>( mIDPool, GenericSpawner<Goblin>() ));
//			break;
//		}
//		
//		break;
//	case objectIDs::bush:
//		break;
//	case objectIDs::tree:
//		break;
//	}
//	return mIDPool++;
//}

int GameObjectManager::addGameObject( GameObjectClass *object )
{
	GameClass *GC = Game::getInstance();
	GC->mGameObjects.insert( std::pair<int, GameObjectClass *>( mIDPool, object ));
	return mIDPool++;
}


void GameObjectManager::update()
{
	GameClass *GC = Game::getInstance();
	for( mGameObject_iter i = GC->mGameObjects.begin(); i != GC->mGameObjects.end(); i++ )
	{
		if( !i->second->alive() )
		{
			GC->mGameObjects.erase( i );
			i = GC->mGameObjects.begin();
		}
	}
}