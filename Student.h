#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <map>
#include "Class.h"
using namespace std;

/**
 * @brief Class that represents a student.
 */

class Student
{
private:
    int studentCode;
    string studentName;
    // ucCode -> class
    map<string, Class> classes;

public:
    // Student constructor
    Student();
    Student(int studentCode, const string &studentName);

    // Set & Getter -> studentCode
    int getStudentCode() const;

    // Set & Getter -> studentName
    string getStudentName() const;

    // classes related methods
    void addClass(const Class &newClass);
    void removeClass(const string &classCode);
    map<string, Class> getAllClasses() const;
};

#endif