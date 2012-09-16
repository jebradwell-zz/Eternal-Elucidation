#ifndef GAME_SHUTDOWN_H
#define GAME_SHUTDOWN_H

#include "Tasks.h"

class GameShutdown : public Task
{
public:
	GameShutdown();
	void Update();
private:
};

#endif //GAME_SHUTDOWN_H