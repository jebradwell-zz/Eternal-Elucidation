#ifndef TASK_H
#define TASK_H

class Task
{
public:
	Task(){};
	virtual void Update() = 0;
};

#endif //TASK_H