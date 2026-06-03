#include "Task.h"

Task::Task(bool setPrio, bool setCompleted, short setId, DueDate setDate, std::string setTask) :
	priority{ setPrio }, completed{ setCompleted }, id{ setId }, date{ setDate }, task{ setTask } {}

std::ostream& operator<<(std::ostream& os, Task& task) {
	os << task.task << ' ';
	if (task.priority) {
		if (task.completed) {
			os << "*DONE*" << ' ';
		}
		else {
			os << task.date << ' ';
		}
	}
	else
	{
		if (task.completed) {
			os << "*DONE*" << ' ';
		}
	}
	os << '(' << task.id << ')';
	return os;
}