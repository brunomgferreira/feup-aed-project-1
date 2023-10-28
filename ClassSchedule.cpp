#include "ClassSchedule.h"

/**
 * @brief Constructor of the class ClassSchedule. weekday, timeInterval and type are set to the given values.
 * @details Time complexity: O(1)
 * @param weekday weekday of the class
 * @param timeInterval start time and end time of the class
 * @param type type of the class
 */

ClassSchedule::ClassSchedule(const string &weekday, const TimeInterval &timeInterval, const string &type)
    : weekday(weekday), timeInterval(timeInterval), type(type) {}


/**
* @brief Returns the weekday of the class.
* @details Time complexity: O(1)
* @return weekday of the class
*/

const string &ClassSchedule::getWeekday() const
{
    return this->weekday;
}

/**
* @brief Returns the time interval of the class.
* @details Time complexity: O(1)
* @return timeInterval of the class
*/

// Set & Getter -> timeInterval
TimeInterval ClassSchedule::getTimeInterval() const
{
    return this->timeInterval;
}

/**
* @brief Returns the start hour of the class.
* @details Time complexity: O(1)
* @return start hour of the class
*/

double ClassSchedule::getStartHour() const
{
    return this->timeInterval.startHour + this->timeInterval.startMinute / 60.0;
}

/**
* @brief Returns the duration of the class.
* @details Time complexity: O(1)
* @return duration of the class
*/

double ClassSchedule::getDuration() const
{
    return (this->timeInterval.endHour + this->timeInterval.endMinute / 60.0) - (this->timeInterval.startHour + this->timeInterval.startMinute / 60.0);
}

/*
string TimeInterval::getTimeIntervalAsString() const
{
    string res = to_string(this->startHour) + ":" + to_string(this->startMinute) + " " + to_string(this->endHour) + ":" + to_string(this->endMinute);
    return res;
}
*/

/**
* @brief Returns the type of the class.
* @details Time complexity: O(1)
* @return startHour of the class
*/

string ClassSchedule::getType() const
{
    return this->type;
}

/**
* @brief Returns the type of the class.
* @details Time complexity: O(1)
* @return type of the class
*/

void ClassSchedule::setType(const string &newType)
{
    this->type = newType;
}