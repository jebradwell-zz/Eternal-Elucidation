#ifndef SPAWNER_H
#define SPAWNER_H

//#include <iostream>

#include <vector>
#include <SFML/Graphics.hpp>
#include "Goblin.h"


class Spawner
{
public:
	Spawner( int x, int y, int radius, sf::Image *img, int tick = 1, double timeInterval = 60 /*60 seconds*/ );	
	void update( sf::RenderWindow &App, const sf::Sprite &player  );
	unsigned int Count(){return mGoblinVec.size();}
private:
	void CreateSpawn();
	void DeleteSpawn();
	int mXStart;
	int mYStart;
	int mRadius;
	int mSpawnPerTick;
	double mTimeInterval;
	sf::Image *mImage;
	sf::Clock mClock;
	std::vector<Goblin *> mGoblinVec;
};

#endif
