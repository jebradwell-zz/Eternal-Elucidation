#ifndef TESTING_H
#define TESTING_H

#include "Tasks.h"

#include "map.h"

class Testing : public Task
{
public:
	Testing();
	void Update();
private:
	void printMap( Map &map);
};

#endif //TESTING_H