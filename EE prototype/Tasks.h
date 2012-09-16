#ifndef TASKS_H
#define TASKS_H

#include <vector>

#include "Task.h"

class Tasks
{
public:
	Tasks(){};
	typedef std::vector<Task*>::iterator iterator;
	typedef std::vector<Task*>::const_iterator const_iterator;	
	iterator begin(){return this->tasks.begin();}
	iterator end(){return this->tasks.end();}
	const_iterator begin() const{return this->tasks.begin();}
	const_iterator end() const {return this->tasks.end();}
	std::vector<Task*> tasks;
};

#endif //TASKS_H