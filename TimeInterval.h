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
    /**
 * @brief Constructor for the TimeInterval class.
 *
 * @details Initializes a TimeInterval object based on the provided start time and duration.
 * The TimeInterval represents a time interval with start and end times in hours
 * and minutes.
 *@details Time complexity: O(1)
 * @param startTime The start time of the time interval as a floating-point number.
 * @param duration The duration of the time interval as a floating-point number.
     */
    TimeInterval(double startTime, double duration);
    /**
 * @brief Get the string representation of the TimeInterval.
 *
 * @details Returns a string representation of the TimeInterval in the format "[hh:mm-hh:mm]".
 *@details Time complexity: O(1)
 * @return A string representing the TimeInterval.
     */
    string getTimeIntervalAsString() const;
};

#endif
