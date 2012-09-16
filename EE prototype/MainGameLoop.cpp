#include "MainGameLoop.h"

#include "LevelGameLoop.h"
#include "LevelInit.h"
#include "LevelShutdown.h"

MainGameLoop::MainGameLoop()
{
}
void MainGameLoop::Update()
{
	//Create GameClass which holds all the global main game loop
	//GameClass *GCinstance = Singleton<GameClass>::getInstance();

	//These are the tasks and there order in which they are iterated through:	
	//LevelInit();
	//LevelGameLoop();
	//LevelShutDown();

	Tasks MainGameLoopTasks;

	LevelInit levelinit;
	LevelGameLoop levelgameloop;
	LevelShutdown levelshutdown;

	MainGameLoopTasks.tasks.push_back(&levelinit);
	MainGameLoopTasks.tasks.push_back(&levelgameloop);
	MainGameLoopTasks.tasks.push_back(&levelshutdown);

	//**********************************************************************
	//If you would like to change the order in which tasks are executed 
	//then look in the GameInit file for there push_back calls and re-order
	//them there.
	//**********************************************************************

	for( Tasks::iterator it = MainGameLoopTasks.begin(); it != MainGameLoopTasks.end(); ++it )
	{
	   //NOTE: gcc complained that task was an unused variable, so I'm getting
	   //rid of it
	   //-Ron
		//Task *task = *it;
		(*it)->Update();
	}
}