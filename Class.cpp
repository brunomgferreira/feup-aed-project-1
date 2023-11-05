#include "Class.h"

#include <iostream>
#include <string>

using namespace std;



Class::Class() {}


Class::Class(const string& ucCode, const string& classCode)
    : ucCode(ucCode), classCode(classCode) {}


string Class::getUcCode() const { return this->ucCode; }


string Class::getClassCode() const { return this->classCode; }


void Class::addClassSchedule(const ClassSchedule& newClassSchedule) {
    this->classSchedules.push_back(newClassSchedule);
}


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


void Class::addStudent(const int newStudentCode) {
    this->students.insert(newStudentCode);
}


void Class::removeStudent(const int studentCode) {
    this->students.erase(studentCode);
}


set<int> Class::getAllStudents() const { return this->students; }


int Class::numberStudents() const { return this->students.size(); }


bool Class::hasVacancies() const { return (numberStudents() < MAX_STUDENTS); }


int Class::numberVacancies() const { return MAX_STUDENTS - numberStudents();}
