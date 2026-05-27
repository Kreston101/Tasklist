#include "Task.h"

Task::Task(bool sP, short sPN, DueDate sD, std::string sT, std::string sE) :
	priority{ sP }, prioNum{ sPN }, date{ sD }, task{ sT }, extra{ sE } {}

Task::Task(bool sP, bool fin, short sPN, DueDate sD, std::string sT, std::string sE) :
	priority{ sP }, completed{ fin }, prioNum{ sPN }, date{ sD }, task{ sT }, extra{ sE } {}

std::ostream& operator<<(std::ostream& os, Task& task) {
	if (task.priority) {
		os << task.task << ' ';
		if (task.completed) {
			os << "*DONE*";
		}
		else {
			os << task.date << ' ';
			os << task.extra;
		}
	}
	else
	{
		os << task.task << ' ';
		if (task.completed) {
			os << "*DONE*";
		}
		else {
			os << task.extra;
		}
	}
	return os;
}