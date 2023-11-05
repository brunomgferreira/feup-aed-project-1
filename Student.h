#ifndef STUDENT_H
#define STUDENT_H

#include <map>
#include <string>

#include "Class.h"
using namespace std;

/**
 * @brief Class that represents a student.
 */

class Student {
   private:
    int studentCode;
    string studentName;
    // ucCode -> class
    map<string, Class> classes;

   public:
    // CONSTRUCTORS
    /**
 * @brief Default constructor for the Student class.
 *
 * @details This default constructor creates a new instance of the Student class without
 * specifying the student code or name. It initializes the Student with default values.
 * @details Time complexity: O(1)
     */
    Student();
    /**
 * @brief Constructor for the Student class.
 *
 * @details Initializes a new instance of the Student class with the provided student code
 * and student name.
 * @details Time complexity: O(1)
 *
 * @param studentCode An integer representing the unique code of the student.
 * @param studentName A string representing the name of the student.
     */
    Student(int studentCode, const string &studentName);

    // GETTERS
    /**
 * @brief Retrieves the student code of the Student.
 *
 * @details This method returns the unique student code associated with the Student.
 * @details Time complexity: O(1)
 *
 * @return An integer representing the student code.
     */
    int getStudentCode() const;
    /**
 * @brief Retrieves the name of the Student.
 *
 * @details This method returns the name of the Student.
 * @details Time complexity: O(1)
 *
 * @return A string representing the name of the Student.
     */
    string getStudentName() const;
    /**
 * @brief Retrieves all classes associated with the Student.
 *
 * @details Method returns a map containing all the classes associated with the Student.
 * The map is keyed by the UC (Unit Course) code and contains Class objects.
 * @details Time complexity: O(1)
 *
 * @return A map where the keys are UC codes, and the values are Class objects.
     */
    map<string, Class> getAllClasses() const;

    // Class related methods
    /**
    * @brief Adds a new Class to the Student's list of classes.
    *
    * @details This method adds a new Class, represented by 'newClass', to the Student's list
    * of classes. The Class is associated with the UC (Unit Course) code, which is used as
    * the key in the list of classes.
    * @details Time complexity: O(log n)
    *
    * @param newClass The Class to add to the Student's list of classes.
    */
    void addClass(const Class &newClass);
    /**
 * @brief Removes a Class from the Student's list of classes by UC code.
 *
 * @details method removes a Class from the Student's list of classes based on the provided UC (Unit Course) code.
 * @details Time complexity: O(log n)
 *
 * @param ucCode A string representing the UC code of the Class to be removed.
     */
    void removeClass(const string &ucCode);
    /**
 * @brief Finds a conflicting Class based on UC code and destination Class.
 *
 * @details Method searches for a conflicting Class among the Student's classes based
 * on the provided UC code and destination Class. It checks if any of the Student's
 * classes in the same UC overlap with the destination Class. If a conflict is found,
 * it returns the Class code of the conflicting Class.
 * @details Time complexity: sem complexity
 *
 * @param ucCode A string representing the UC (Unit Course) code of the destination Class.
 * @param originClassCode A string representing the code of the Class the Student wants to leave.
 * @param destinyClass The Class the Student wants to join.
 *
 * @return A string representing the Class code of the conflicting Class, or an empty string
 * if no conflict is found.
     */
    string findConflictClass(const string& ucCode, const string &originClassCode,
                     const Class& destinyClass) const;
    /**
 * @brief Retrieves the Class code of the Student for a specific UC.
 *
 * @details This method returns the Class code of the Student for the provided UC (Unit Course) code.
 * @details Time complexity: O(log n)
 *
 * @param ucCode A string representing the UC code for which the Student's Class code is requested.
 *
 * @return A string representing the Class code of the Student in the specified UC, or an empty string
 * if the UC code is not found in the Student's classes.
     */
    string getUcClassCode(const string &ucCode) const;

    // Ucs related methods
    /**
 * @brief Retrieves the number of Unit Courses (UCs) associated with the Student.
 *
 * @details This method returns the count of Unit Courses associated with the Student, which
 * represents the number of UCs the Student is enrolled in.
 * @details Time complexity: O(1)
 *
 * @return An integer representing the number of Unit Courses the Student is enrolled in.
     */
    int numberOfUcs() const;
    /**
 * @brief Checks if the Student is enrolled in a specific Unit Course (UC).
 *
 * @details This method checks if the Student is enrolled in a Unit Course with the provided UC (Unit Course) code.
 * It searches through the Student's classes to find a match.
 * @details Time complexity: O(n)
 *
 * @param ucCode A string representing the UC code to check for enrollment.
 *
 * @return true if the Student is enrolled in the specified UC; otherwise, false.
     */
    bool hasUc(const string &ucCode) const;

    /**
 * @brief Generates a formatted string representation of the Student's information.
 *
 * @details This method constructs a formatted string that represents the Student's information,
 * including the student code, student name, and a list of the Unit Courses (UCs) and their
 * associated Class codes that the Student is enrolled in.
 * @details Time complexity: O(n)
 *
 * @return A string containing the formatted representation of the Student's information.
     */
    string getStudentAsString() const;
};

#endif
