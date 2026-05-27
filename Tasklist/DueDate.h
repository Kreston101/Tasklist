#pragma once
#include <iostream>

struct DueDate
{
	short day;
	short month;

	DueDate() = delete;
	DueDate(short day, short month);
};

std::ostream& operator<<(std::ostream& os, DueDate& date);
