#include "TimeInterval.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @brief Constructor of the struct TimeInterval. startHour, startMinute, endHour, and endMinute are set to the given values.
 * @details Time complexity: O(1)
 * @param startTime start time of the time interval
 * @param duration duration of the time interval
 */


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
    res << "[" << std::setfill('0') << std::setw(2) << startHour << ":" << std::setfill('0') << std::setw(2) << startMinute
        << "-" << std::setfill('0') << std::setw(2) << endHour << ":" << std::setfill('0') << std::setw(2) << endMinute << "]";
    return res.str();
}