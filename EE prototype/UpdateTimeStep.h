#ifndef UPDATE_TIME_STEP
#define UPDATE_TIME_STEP

#include "Tasks.h"

class UpdateTimeStep : public Task
{
public:
	UpdateTimeStep();
	void Update();
private:
};

#endif //UPDATE_TIME_STEP