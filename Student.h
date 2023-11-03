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
    bool verifyClass(const string &originClassCode,
                     const string &destinyClassCode) const;
    string getUcClassCode(const string &ucCode) const;
    // Ucs
    int numberOfUcs() const;
    bool hasUc(const string &ucCode) const;

    string getStudentAsString() const;
};

#endif
