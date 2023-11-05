

#ifndef CLASS_H
#define CLASS_H

#include <set>
#include <vector>

#include "ClassSchedule.h"
using namespace std;

/**
 * @brief Class that represents a class for a given UC.
 */
class Class {
   private:
    string ucCode;
    string classCode;
    vector<ClassSchedule> classSchedules;
    set<int> students;
    const static int MAX_STUDENTS = 30;

   public:
    // CLASS CONSTRUCTORS
    /**
 * @brief Default constructor for the Class.
 *
 * @details This default constructor creates a new instance of the Class with no specific
 * UC code or class code. It can be used to initialize an empty Class.
 * @details Time complexity: O(1)
     */
    Class();
    /**
 * @brief Class constructor with UC code and class code.
 *
 * @details Initializes a new instance of the Class with the provided UC code and class code.
 * @details Time complexity: O(1)
 *
 * @param ucCode A string representing the UC (Unit Course) code associated with the Class.
 * @param classCode A string representing the unique code of the Class.
     */
    Class(const string& ucCode, const string& classCode);

    // GETTERS
    /**
 * @brief Getter method to retrieve the UC code of the Class.
 *
 * @details This method returns the UC code associated with the Class.
 * @details Time complexity: O(1)
 *
 * @return A string containing the UC code of the Class.
     */
    string getUcCode() const;
    /**
 * @brief Getter method to retrieve the Class code of the Class.
 *
 *
 *
 * @details This method returns the Class code associated with the Class.
 * @details Time complexity: O(1)
 *
 * @return A string containing the Class code of the Class.
     */
    string getClassCode() const;

    // ClassSchedule related methods
    /**
 * @brief Adds a new class schedule to the Class.
 *
 * @details This method appends a new class schedule, represented by 'newClassSchedule',
 * to the list of schedules associated with the Class.
 * @details Time complexity: O(1)
 *
 * @param newClassSchedule The ClassSchedule to add to the Class.
     */
    void addClassSchedule(const ClassSchedule& newClassSchedule);
    /**
 * @brief Retrieves all class schedules associated with the Class.
 *
 * @details This method returns a vector containing all the class schedules associated
 * with the Class, providing access to the complete list of schedules.
 * @details Time complexity: O(1)
 *
 * @return A vector of ClassSchedule objects representing the class schedules.
     */
    vector<ClassSchedule> getAllClassSchedules() const;
    /**
 * @brief Checks for invalid overlaps between two classes' schedules.
 *
 * @details This method iterates through the schedules of the current class and the
 * provided 'destinyClass', comparing each pair of schedules to check if they
 * have invalid overlaps. An overlap is considered invalid if it conflicts with
 * the timing of another schedule.
 * @details Time complexity: Sem complexity
 *
 * @param destinyClass The Class to compare schedules with.
 *
 * @return true if there are invalid overlaps between the schedules of the
 * current class and the 'destinyClass'; otherwise, false.
     */
    bool invalidOverlaps(const Class& other) const;

    // Students related methods
    /**
 * @brief Adds a new student (by student code) to the Class.
 *
 * @details This method adds a new student to the Class by including the student's code
 * in the list of students associated with the Class.
 * @details Time complexity: O(log n)
 *
 * @param newStudentCode An integer representing the code of the new student.
     */
    void addStudent(int newStudentCode);
    /**
 * @brief Removes a student from the Class by student code.
 *
 * @details This method removes a student from the Class based on the provided student code.
 * If a student with the given code is found in the Class, they will be removed.
 * @details Time complexity: O(log n)
 *
 * @param studentCode An integer representing the code of the student to be removed.
     */
    void removeStudent(int studentCode);
    /**
 * @brief Retrieves all students' codes associated with the Class.
 *
 * @details This method returns a set containing the student codes of all students
 * associated with the Class, allowing access to the complete list of students.
 * @details Time complexity: O(1)
 *
 * @return A set of integers representing the student codes.
     */
    set<int> getAllStudents() const;
    /**
 * @brief Retrieves the number of students enrolled in the Class.
 *
 * @details This method returns the count of students currently associated with the Class,
 * providing the total number of students.
 * @details Time complexity: O(1)
 *
 * @return An integer representing the number of students.
     */
    int numberStudents() const;
    // Vacancy related methods
    /**
 * @brief Checks if the Class has available vacancies for students.
 *
 * @details This method checks whether the Class has available vacancies for students by
 * comparing the number of enrolled students with the maximum allowed capacity.
 * @details Time complexity: O(1)
 *
 * @return true if there are vacancies in the Class; false if the maximum
 * capacity has been reached.
     */
    bool hasVacancies() const;
    /**
 * @brief Retrieves the number of available vacancies in the Class.
 *
 * @details This method calculates and returns the number of available vacancies in the Class
 * by subtracting the current number of enrolled students from the maximum allowed capacity.
 * @details Time complexity: O(1)
 *
 * @return An integer representing the number of available vacancies in the Class.
     */
    int numberVacancies() const;
};

#endif
