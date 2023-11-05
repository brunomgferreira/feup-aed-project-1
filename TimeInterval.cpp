#include "TimeInterval.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;




TimeInterval::TimeInterval(double startTime, double duration)
{
    this->startHour = static_cast<int>(startTime);
    this->startMinute = (startTime - startHour) * 60;

    double endTime = startTime + duration;

    this->endHour = static_cast<int>(endTime);
    this->endMinute = (endTime - endHour) * 60;
}

string TimeInterval::getTimeIntervalAsString() const {
    stringstream res;
    res << "[" << setfill('0') << setw(2) << startHour << ":" << setfill('0') << setw(2) << startMinute
        << "-" << setfill('0') << setw(2) << endHour << ":" << setfill('0') << setw(2) << endMinute << "]";
    return res.str();
}