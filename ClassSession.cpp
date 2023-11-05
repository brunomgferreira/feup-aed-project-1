#include "ClassSession.h"

#include <unordered_map>

ClassSession::ClassSession(const string &weekday,
                             const TimeInterval &timeInterval,
                             const string &type)
    : weekday(weekday), timeInterval(timeInterval), type(type) {}



const string &ClassSession::getWeekday() const { return this->weekday; }



TimeInterval ClassSession::getTimeInterval() const {
    return this->timeInterval;
}



double ClassSession::getStartHour() const {
    return this->timeInterval.startHour + this->timeInterval.startMinute / 60.0;
}


double ClassSession::getDuration() const {
    return (this->timeInterval.endHour + this->timeInterval.endMinute / 60.0) -
           (this->timeInterval.startHour +
            this->timeInterval.startMinute / 60.0);
}


string ClassSession::getType() const { return this->type; }


bool ClassSession::overlaps(const ClassSession &schedule) const {
    int start1 = timeInterval.startHour * 60 + timeInterval.startMinute;
    int end1 = timeInterval.endHour * 60 + timeInterval.endMinute;
    int start2 = schedule.timeInterval.startHour * 60 +
                 schedule.timeInterval.startMinute;
    int end2 =
        schedule.timeInterval.endHour * 60 + schedule.timeInterval.endMinute;
    return (weekday == schedule.weekday &&(
                (start2 >= start1 && start2 <= end1) ||
            (start1 >= start2 && start1 <= end2)));
}

bool ClassSession::invalidOverlaps(const ClassSession &schedule) const {
    return (type != "T" && schedule.type != "T" && overlaps(schedule));
}


bool ClassSession::operator<(const ClassSession &other) const {
    unordered_map<string, int> weekdayMap = {
            {"Monday", 0},
            {"Tuesday", 1},
            {"Wednesday", 2},
            {"Thursday", 3},
            {"Friday", 4},
    };

    int thisWeekday = weekdayMap[this->getWeekday()];
    int otherWeekday = weekdayMap[other.getWeekday()];


    if (thisWeekday < otherWeekday)
        return true;
    else if (thisWeekday > otherWeekday)
        return false;


    return this->getStartHour() < other.getStartHour();
}
