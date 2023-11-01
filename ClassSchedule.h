#ifndef CLASSSCHEDULE_H
#define CLASSSCHEDULE_H

#include <string>

#include "TimeInterval.h"
using namespace std;

/**
 * @brief Class that stores a class schedule for a given class.
 */

class ClassSchedule {
   private:
    string weekday;
    TimeInterval timeInterval;
    string type;

   public:
    // Class constructor constructor
    ClassSchedule(const string &weekday, const TimeInterval &time,
                  const string &type);

    // Set & Getter -> weekday
    const string &getWeekday() const;

    // Set & Getter -> timeInterval
    TimeInterval getTimeInterval() const;
    double getStartHour() const;
    double getDuration() const;

    // Set & Getter -> type
    string getType() const;
    void setType(const string &newType);

    // Compare Schedules
    bool overlaps(const ClassSchedule &schedule) const;
    bool invalidOverlaps(const ClassSchedule &schedule) const;
};

#endif
