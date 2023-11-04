#include <sstream>
#include <iomanip>
#include "Student.h"
using namespace std;

/**
 * @brief Standard constructor of the class Student.
 * @details Time complexity: O(1)
 */

Student::Student() = default;

/**
 * @brief Constructor of the class Student. studentCode and studentName are set
 * to the given values.
 * @details Time complexity: O(1)
 * @param studentCode code of the student
 * @param studentName name of the student
 */

Student::Student(int studentCode, const string& studentName) {
    this->studentCode = studentCode;
    this->studentName = studentName;
}

/**
 * @brief Returns the studentCode of the student.
 * @details Time complexity: O(1)
 * @return studentCode code of the student
 */

int Student::getStudentCode() const { return this->studentCode; }

/**
 * @brief Returns the studentName of the student.
 * @details Time complexity: O(1)
 * @return studentName name of the student
 */

string Student::getStudentName() const { return this->studentName; }

/**
 * @brief Adds a new class to the classes
 * @details Time complexity: O(log(n))
 * @param newClass new class of the student
 */

void Student::addClass(const Class& newClass) {
    this->classes[newClass.getUcCode()] = newClass;
}

// VAI SER PARA MUDAR ?????? -> É MELHOR FAZER A TROCA ENTRE DUAS CLASSES NUM
// MESMA UC (+ rapido)

/**
 * @brief Removes a class from the classes in student
 * @details Time complexity: TODO
 * @param classCode class code of the class to be removed
 */

void Student::removeClass(const string& classCode) {
    // TODO
}

/**
 * @brief Returns all the classes of student.
 * @details Time complexity: O(1)
 * @return classes all the classes of the student
 */

map<string, Class> Student::getAllClasses() const { return this->classes; }

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

/*
 *@brief Return the number of Ucs the student is in.
 *@details Time complexity: O(1)
 *@return the number of Ucs a student is in.
 */

int Student::numberOfUcs() const { return classes.size(); }

/*
 *@brief Checks if a students is enrolled in a UC
 *@details Time complexity: O(n)
 *@param ucCode Code of the UC to check
 *@return True if the student enrolles in that UC, otherwise False
 */
bool Student::hasUc(const string& ucCode) const {
    for (const auto [classCode, c] : classes) {
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
