

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
    // Class constructor
    Class();
    Class(const string& ucCode, const string& classCode);

    // Set & Getter -> ucCode
    string getUcCode() const;

    // Set & Getter -> classCode
    string getClassCode() const;

    // classSchedules related methods
    void addClassSchedule(const ClassSchedule& newClassSchedule);
    vector<ClassSchedule> getAllClassSchedules() const;
    bool invalidOverlaps(const Class& other) const;

    // students related methods
    void addStudent(int newStudentCode);
    void removeStudent(int studentCode);
    set<int> getAllStudents() const;
    int numberStudents() const;

    bool hasVacancies() const;
    int numberVacancies() const;
};

#endif
