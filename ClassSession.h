#ifndef CLASSSCHEDULE_H
#define CLASSSCHEDULE_H

#include <string>

#include "TimeInterval.h"
using namespace std;

/**
 * @brief Class that stores a class schedule for a given class.
 */

class ClassSession {
   private:
    string weekday;
    TimeInterval timeInterval;
    string type;

   public:
    // Constructor
    /**
 * @brief Constructs a ClassSession object with the specified attributes.
 *
 * @details Initializes a ClassSession object with the provided weekday, time interval,
 * and session type.
 * @details Time complexity: O(1)
 *
 * @param weekday The weekday on which the class session occurs (e.g., "Monday").
 * @param timeInterval The time interval during which the class session takes place.
 * @param type The type of the class session (e.g., "Lecture" or "Lab").
     */
    ClassSession(const string &weekday, const TimeInterval &time,
                  const string &type);

    // Getters
    /**
 * @brief Retrieves the weekday of the class session.
 *
 * @details This method returns a constant reference to the weekday on which
 * the class session occurs.
 * @details Time complexity: O(1)
 *
 * @return A constant reference to the weekday of the class session.
     */
    const string &getWeekday() const;
    /**
 * @brief Retrieves the time interval of the class session.
 *
 * @details This method returns the time interval during which the class session
 * occurs.
 * @details Time complexity: O(1)
 *
 * @return The time interval of the class session.
     */
    TimeInterval getTimeInterval() const;
    /**
 * @brief Retrieves the start hour of the class session.
 *
 * @details This method returns the start hour of the class session as a double
 * value, including the minutes in fractional part.
 * @details Time complexity: O(1)
 *
 * @return The start hour of the class session.
     */
    double getStartHour() const;
    /**
 * @brief Retrieves the duration of the class session in hours.
 *
 * @details This method calculates and returns the duration of the class session
 * in hours, taking into account both the start and end times, including
 * minutes.
 * @details Time complexity: O(1)
 *
 * @return The duration of the class session in hours.
     */
    double getDuration() const;
    /**
 * @brief Retrieves the type of the class session.
 *@details Time complexity: O(1)
 * @return The type of the class session, such as "T", "TP" or "P".
     */
    string getType() const;

    // Comparation
    /**
 * @brief Checks if the current class session overlaps with another class session.
 *
 * @details This method determines whether the current class session's time interval
 * overlaps with the time interval of another class session on the same day (weekday).
 * @details Time complexity: O(1)
 *
 * @param schedule The other class session to compare with.
 * @return True if there is an overlap in time and the same weekday, otherwise false.
     */
    bool overlaps(const ClassSession &schedule) const;
    /**
 * @brief Checks if the current class session has an invalid overlap with another class session.
 *
 * @details This method determines whether the current class session has an invalid overlap with another class session on the same day (weekday) and time interval. An overlap is considered invalid when both class sessions are not of type "T" (tutorial) and there is a time overlap.
 *@details Time complexity: O(1)
 * @param schedule The other class session to compare with.
 * @return True if there is an invalid overlap, otherwise false.
     */
    bool invalidOverlaps(const ClassSession &schedule) const;
    /**
 * @brief Determines the order of class sessions based on weekdays and start times.
 *
 * @details This method is used to compare two class sessions and establish their order.
     * Class sessions are compared first by weekdays (Monday to Friday) and then by
     * their start times. If this class session is scheduled to occur earlier
     * in the week or at an earlier time of day than the other class session,
     * it is considered to be less than the other class session.
 *@details Time complexity: O(1)
 * @param other The other class session to compare with.
 * @return True if this class session is less than the other, otherwise false.
     */
    bool operator<(const ClassSession &other) const;
};

#endif
