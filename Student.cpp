#include <sstream>
#include <iomanip>
#include "Student.h"
using namespace std;



Student::Student() = default;


Student::Student(int studentCode, const string& studentName) {
    this->studentCode = studentCode;
    this->studentName = studentName;
}


int Student::getStudentCode() const { return this->studentCode; }


string Student::getStudentName() const { return this->studentName; }


map<string, Class> Student::getAllClasses() const { return this->classes; }


void Student::addClass(const Class& newClass) {
    this->classes[newClass.getUcCode()] = newClass;
}


void Student::removeClass(const string& ucCode) {
    this->classes.erase(ucCode);
}


string Student::findConflictClass(const std::string& ucCode, const std::string& originClassCode, const Class& destinyClass) const {
    for (const auto& [classUcCode, c] : classes) {
        if (ucCode == classUcCode && destinyClass.invalidOverlaps(c)) {
            return c.getClassCode();
        }
    }
    return "";
}


string Student::getUcClassCode(const string& ucCode) const {
    return classes.at(ucCode).getClassCode();
}


int Student::numberOfUcs() const { return classes.size(); }


bool Student::hasUc(const string& ucCode) const {
    for (const auto& [classCode, c] : classes) {
        if (c.getUcCode() == ucCode) {
            return true;
        }
    }
    return false;
}


string Student::getStudentAsString() const {
    stringstream res;
    res << studentCode << " - " << left << setw(25) << studentName + " : ";
    for(const auto& [ucCode, c] : classes) {
        res << left << setw(20) << "[" + ucCode + "-" + c.getClassCode() + "] ";
    }
    return res.str();
}
