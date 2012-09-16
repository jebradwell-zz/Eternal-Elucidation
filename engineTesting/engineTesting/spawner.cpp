#include "spawner.h"
#include <stdio.h>
#include <time.h>

#define SQRT2OVER2 0.70710678118654752440084436210485f
Spawner::Spawner( int x, int y, int radius, sf::Image *img, int tick, double timeInterval )
{
	srand ( (unsigned int) time(NULL) );
	mXStart = x;
	mYStart = y;
	mRadius = radius;
	mImage = img;
	mSpawnPerTick = tick;
	mTimeInterval = timeInterval;
	mClock.Reset();
	
}

void Spawner::CreateSpawn()
{
	int xlen ;
	int ylen;
	float speed;
	for(int i = 0; i < mSpawnPerTick; i++ )
	{
		//do a random bool check... randomly pick between 1-100
		//then if it is greater than half a hundrend i.e. 50 
		//add else subract to get a well estabolished radius
		do
		{
			if( (int)(((100 + 1) * rand()) / (RAND_MAX + 1.0)) > 50 )
				xlen = -((mRadius + 1) * rand()) / (RAND_MAX + 1.0);
			else
				xlen = ((mRadius + 1) * rand()) / (RAND_MAX + 1.0);

			if( (int)(((100 + 1) * rand()) / (RAND_MAX + 1.0)) > 50 )
				ylen = -((mRadius + 1) * rand()) / (RAND_MAX + 1.0);
			else
				ylen = ((mRadius + 1) * rand()) / (RAND_MAX + 1.0);
		}while ( abs(xlen)* SQRT2OVER2 + abs(ylen) * SQRT2OVER2 > mRadius );

		speed = (float)(((300 + 1) * rand()) / (RAND_MAX + 1.0)) / 100.0f + 2;
		//mGoblinVec.push_back(new Goblin( mXStart + xlen, mYStart + ylen));
	}
}

void Spawner::DeleteSpawn()
{
	for( int i = 0; i < mGoblinVec.size(); i++ )
	{
		//if( !mGoblinVec[i]->Alive() )
		//{
		//	mGoblinVec.erase( mGoblinVec.begin() + i);
		//	i--;
		//}
	}
}
void Spawner::update( sf::RenderWindow &App, const sf::Sprite &player )
{
	//if( mClock.GetElapsedTime() > mTimeInterval ) 
	//{
	//	mClock.Reset();
	//	CreateSpawn();
	//}
	//DeleteSpawn();
	//for( int i = 0; i < mGoblinVec.size(); i++ )
	//{
	//	mGoblinVec[i]->update(App, player);
	//	mGoblinVec[i]->draw(App);
	//}
}