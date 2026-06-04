#pragma once
#include <iostream>
#include <string>
#include "DueDate.h"

struct Task
{
	//lp, hp
	//store format
	//1 1 0 1/1 TaskName
	bool priority;
	bool completed = 0;
	short id;
	DueDate date;
	std::string task;

	//Rule of zero, woooo
	Task(bool setPrio, bool setCompleted, short setId, DueDate setDate, std::string setTask);
};

std::ostream& operator<<(std::ostream& os, Task& task);