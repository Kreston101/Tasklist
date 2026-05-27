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
	short prioNum;
	DueDate date;
	std::string task;
	std::string extra;

	Task() = delete;
	//ctor NOT EQUAL TO input handler
	Task(bool sP, short sPN, DueDate sD, std::string sT, std::string sE);
	//one of these is redundant...
	Task(bool sP, bool fin, short sPN, DueDate sD, std::string sT, std::string sE);
};

std::ostream& operator<<(std::ostream& os, Task& task);