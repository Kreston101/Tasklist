#include "DueDate.h"

DueDate::DueDate(short setDay, short setMon) : day{ setDay }, month{ setMon } {}

std::ostream& operator<<(std::ostream& os, DueDate& date) {
	os << date.day << '/' << date.month;
	return os;
}

bool operator<(DueDate const& lhs, DueDate const& rhs) {
	if (lhs.month < rhs.month) {
		return true;
	}
	if (lhs.month == rhs.month && lhs.day < rhs.day) {
		return true;
	}
	return false;
}