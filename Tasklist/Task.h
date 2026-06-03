#pragma once
#include <iostream>
#include <string>
#include "DueDate.h"

struct Task
{
	//static task count, lp, hp
	//store format
	//1 1 0 1/1 TaskName # Note Section
	bool priority;
	bool completed = 0;
	short id;
	DueDate date;
	std::string task;

	Task() = delete;
	//one of these is redundant...
	Task(bool setPrio, bool setCompleted, short setId, DueDate setDate, std::string setTask);
};

std::ostream& operator<<(std::ostream& os, Task& task);