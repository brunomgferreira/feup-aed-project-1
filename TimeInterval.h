#ifndef TIMEINTERVAL_H
#define TIMEINTERVAL_H

#include <string>

using namespace std;

/**
 * @brief Struct that represents a time interval.
 */

struct TimeInterval
{
    int startHour;
    int startMinute;
    int endHour;
    int endMinute;

    TimeInterval(double startTime, double duration);
    string getTimeIntervalAsString() const;
};

#endif
