#include "LevelGameLoop.h"

#include "GatherInput.h"
#include "RunAI.h"
#include "RunPhysicsSimulations.h"
#include "SendNetworkMessages.h"
#include "UpdateGameEntities.h"
#include "UpdateGameState.h"
#include "UpdateTimeStep.h"
#include "MiscTasks.h"


LevelGameLoop::LevelGameLoop()
{
}
void LevelGameLoop::Update()
{
	//Create GameClass which holds all the global main game loop
	//GameClass *GCinstance = Singleton<GameClass>::getInstance();

	////These are the tasks and there order in which they are iterated through:
	////GatherInput();
	////RunAI();
	////RunPhysicsSimulations();
	////UpdateGameEntities();
	////SendNetworkMessages();
	////UpdatedTimeStep();
	////UpdatedGameState();
	////MiscTasks();
	Tasks LevelGameLoopTasks;

	GatherInput gatherinput;
	RunAI runai;
	RunPhysicsSimulations runphysicssimulations;
	UpdateGameEntities updategameentities;
	SendNetworkMessages sendnetworkmessages;
	UpdateTimeStep updatetimestep;
	UpdateGameState updategamestate;
	MiscTasks misctasks;

	LevelGameLoopTasks.tasks.push_back(&gatherinput);
	LevelGameLoopTasks.tasks.push_back(&runai);
	LevelGameLoopTasks.tasks.push_back(&runphysicssimulations);
	LevelGameLoopTasks.tasks.push_back(&updategameentities);
	LevelGameLoopTasks.tasks.push_back(&sendnetworkmessages);
	LevelGameLoopTasks.tasks.push_back(&updatetimestep);
	LevelGameLoopTasks.tasks.push_back(&updategameentities);
	LevelGameLoopTasks.tasks.push_back(&misctasks);


	/////**********************************************************************
	////If you would like to change the order in which tasks are executed 
	////then look in the GameInit file for there push_back calls and re-order
	////them there.
	////**********************************************************************

	for( Tasks::iterator it = LevelGameLoopTasks.begin(); it != LevelGameLoopTasks.end(); ++it )
	{
	   //NOTE: gcc complained that task was an unused variable, so I'm getting
	   //rid of it
	   //-Ron
		//Task *task = *it;
		(*it)->Update();
	}


}