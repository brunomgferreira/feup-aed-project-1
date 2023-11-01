#include "Class.h"

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Standard constructor of the class Class.
 * @details Time complexity: O(1)
 */

Class::Class() {}

/**
 * @brief Constructor of the class Class. ucCode and classCode are set to the
 * given values.
 * @details Time complexity: O(1)
 * @param ucCode code of the UC
 * @param classCode code of the class
 */

Class::Class(const string& ucCode, const string& classCode)
    : ucCode(ucCode), classCode(classCode) {}

/**
 * @brief Returns the ucCode of the class.
 * @details Time complexity: O(1)
 * @return ucCode code of the UC of the class
 */

string Class::getUcCode() const { return this->ucCode; }

/**
 * @brief Returns the classCode of the class.
 * @details Time complexity: O(1)
 * @return classCode code of the class
 */

string Class::getClassCode() const { return this->classCode; }

/**
 * @brief Adds a new class schedule to the classSchedules
 * @details Time complexity: O(1)
 * @param newClassSchedule new schedule of a class of the class
 */

void Class::addClassSchedule(const ClassSchedule& newClassSchedule) {
    this->classSchedules.push_back(newClassSchedule);
}

/**
 * @brief Returns all the class's class schedules.
 * @details Time complexity: O(1)
 * @return classSchedules all the classes schedules of the class
 */

vector<ClassSchedule> Class::getAllClassSchedules() const {
    return this->classSchedules;
}

bool Class::invalidOverlaps(const Class& destinyClass) const {
    for (const auto& originalSchedule : classSchedules) {
        for (const auto& addedSchedule : destinyClass.classSchedules) {
            if (addedSchedule.invalidOverlaps(originalSchedule)) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Adds a new student code to the students in the class
 * @details Time complexity: O(log n)
 * @param newStudentCode student code of a new student enrolled in the class
 */

void Class::addStudent(const int newStudentCode) {
    this->students.insert(newStudentCode);
}

/**
 * @brief Removes a student code from the students in the class
 * @details Time complexity: TODO
 * @param studentCode student code of the student to be removed
 */

void Class::removeStudent(const int studentCode) {
    // TODO
}

/**
 * @brief Returns all the class students.
 * @details Time complexity: O(1)
 * @return students all the codes of the students enrolled in the class
 */

set<int> Class::getAllStudents() const { return this->students; }

/*
 *@brief Returns the numbers of students in the class
 *@details Time complexity: O(1)
 *@return Number of students in the class
 */
int Class::numberStudents() const { return this->students.size(); }

/*
 *@brief Checks if the class has vacancy
 *@details Time Complexity: O(1)
 *@return True if the class has vacancy, otherwise False
 */
bool Class::hasVacancies() const { return (numberStudents() < MAX_STUDENTS); }
