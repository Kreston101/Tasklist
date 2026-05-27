#include "DueDate.h"

DueDate::DueDate(short setDay, short setMon) : day{ setDay }, month{ setMon } {}

std::ostream& operator<<(std::ostream& os, DueDate& date) {
	os << date.day << '/' << date.month;
	return os;
}