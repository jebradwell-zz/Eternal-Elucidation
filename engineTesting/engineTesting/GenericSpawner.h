#ifndef GENERIC_SPAWNER_H
#define GENERIC_SPAWNER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <time.h>

#include "GameObjectClass.h" //should we have theses headers if they are already in the GameObjectManager.h header?
#include "GameClass.h" //should we have theses headers if they are already in the GameObjectManager.h header?
#include "GameObjectManager.h"

#define SQRT2OVER2 0.70710678118654752440084436210485f

//Must pass a GameObject class as T, in other words a class that 
//publicly inherits from GameObject class.
template <class GameObjectClass>
class GenericSpawner : public GameObjectClass
{
public:
	static bool Init()
	{
		GameClass *GC = Game::getInstance();
		mApp = GC->App;
		return true;
	}
	GenericSpawner( int x, int y, int radius, int tick = 1, double timeInterval = 60 /*60 seconds*/, int cap = 1 );	
	void update();
	void kill(){ mAlive = false;}
	bool alive(){return mAlive;}
	int Count(){ return mCount; }
private:
	void CreateSpawn();
	void DeleteSpawn();
	int mXStart;
	int mYStart;
	int mRadius;
	int mSpawnPerTick;
	int mCap;
	int mCount;
	bool mAlive;
	float mTime;
	double mTimeInterval;
	static sf::RenderWindow *mApp;
	std::vector<int> mSpawnIDs;
	//std::vector<T *> mTVec;
};

//initialize the static App variable.
template <class GameObjectClass>
sf::RenderWindow *GenericSpawner<GameObjectClass>::mApp;

/*CLASS MEMBER FUNCTIONS START HERE*/
template <class GameObjectClass>
GenericSpawner<GameObjectClass>::GenericSpawner( int x, int y, int radius, int tick, double timeInterval, int cap ):
mXStart(x), mYStart(y), mRadius(radius), mSpawnPerTick(tick), mTimeInterval(timeInterval), mCap(cap), mTime(0), mCount(0), mAlive(true)
{
	GameObjectManager *GOM = GameOM::getInstance();
	GameObjectClass *tmp = this;
	GOM->addGameObject(tmp);
	srand ( (unsigned)time(NULL) );
}

template <class T>
void GenericSpawner<T>::CreateSpawn()
{
	int xlen;
	int ylen;
	GameObjectManager *GOM = GameOM::getInstance();
	//float speed;
	for(int i = 0; i < mSpawnPerTick && mCount < mCap; i++ )
	{
		//do a random bool check... randomly pick between 1-100
		//then if it is greater than half a hundrend i.e. 50 
		//add else subract to get a well estabolished radius
		do
		{
			if( (int)(((100 + 1) * rand()) / (RAND_MAX + 1.0)) > 50 )
				xlen = (int)(-((mRadius + 1) * rand()) / (RAND_MAX + 1.0));
			else
				xlen = (int)(((mRadius + 1) * rand()) / (RAND_MAX + 1.0));

			if( (int)(((100 + 1) * rand()) / (RAND_MAX + 1.0)) > 50 )
				ylen = (int)(-((mRadius + 1) * rand()) / (RAND_MAX + 1.0));
			else
				ylen = (int)(((mRadius + 1) * rand()) / (RAND_MAX + 1.0));
		}while ( xlen * xlen + ylen * ylen > mRadius * mRadius );
		mSpawnIDs.push_back(GOM->addGameObject(new T( mXStart + xlen, mYStart + ylen )));
		mCount++;
		//mTVec.push_back( new T( mXStart + xlen, mYStart + ylen ));
		//mGoblinVec.push_back(new Goblin( mXStart + xlen, mYStart + ylen, speed, mImage ));
		//Load in all the template data from the Game Objects XML for the template class constructor
		//to know how to correctly initialize the class
		//**************VERY VERY VERY IMPORTANT CONCEPT*****************
		//**************VERY VERY VERY IMPORTANT CONCEPT*****************
		//**************VERY VERY VERY IMPORTANT CONCEPT*****************
		//**************VERY VERY VERY IMPORTANT CONCEPT*****************
		/*
		Create a function for all objects in the game which look up there
		individual membor functions by being passed a string with the
		functions name in it. i.e. if a class has methods setSpeed( int speed )
		setJump( float height ) setPosition( float x, float y) then the
		Game object class will have a function call say 
		FunctionLookUp( std::string info ) which will look up the
		correct function from first word in the string passed then it will
		correctly insert the next tokened parts of the strings as parameters
		this allows for an XML file to be created and passed into a constucture
		of a Game Object to set it's memeber variables without needing to 
		know the correct functions to call or what data to pass it at run 
		time. It all comes from the file.
		There will need to be a look up function for the types that are being
		created

		An xml file would look something like this:
		<functions>
			<function name="setRun" values="90" />
			<function name="setJump" values="1.26" />
			<function name="setPosition" values="44.9 89.23" />
		</functions>
		
		the FunctionLookUp( std::string info ) function takes care
		of the conversion of the values into their appropriate types.
		*/
		//**************VERY VERY VERY IMPORTANT CONCEPT*****************
		//**************VERY VERY VERY IMPORTANT CONCEPT*****************
		//**************VERY VERY VERY IMPORTANT CONCEPT*****************
	}
}

template <class T>
void GenericSpawner<T>::DeleteSpawn()
{
	GameClass *GC = Game::getInstance();
	for( unsigned int i = 0; i < mSpawnIDs.size(); i++ )
	{
		//if( !GC->mGameObjects.find(mSpawnIDs[i])->second->alive() )
		//{
		//	GC->mGameObjects.erase(mSpawnIDs[i]);
		//	mSpawnIDs.erase(mSpawnIDs.begin() + i);
		//	i--;
		//	mCount--;
		//}
		if(GC->mGameObjects.find(mSpawnIDs[i]) == GC->mGameObjects.end())
		{
			mSpawnIDs.erase(mSpawnIDs.begin() + i);
			i--;
			mCount--;
		}
	}
	//for( unsigned int i = 0; i < mTVec.size(); i++ )
	//{
	//	if( !mTVec[i]->Alive() )
	//	{
	//		mTVec.erase( mTVec.begin() + i);
	//		//make sure to move back so that we done skip over 
	//		//the element moved into the erased elements spot.
	//		i--;
	//	}
	//}
}

template <class GameObjectClass>
void GenericSpawner<GameObjectClass>::update()
{
	mTime += mApp->GetFrameTime();
	if( mTime > mTimeInterval ) 
	{
		CreateSpawn();
		mTime = 0;
	}
	DeleteSpawn();
	//for( unsigned int i = 0; i < mTVec.size(); i++ )
	//{
	//	mTVec[i]->update(*mApp, player);
	//	mTVec[i]->draw(*mApp);
	//}
}


#endif //GENERIC_SPAWNER_H
