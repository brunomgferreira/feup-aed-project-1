#include "Uc.h"

/**
 * @brief Standard constructor of the class Uc.
 * @details Time complexity: O(1)
 */

Uc::Uc() {}

/**
 * @brief Constructor of the class Uc. ucCode is set to the given value.
 * @details Time complexity: O(1)
 * @param ucCode code of the UC
 */

Uc::Uc(const string &ucCode) { this->ucCode = ucCode; }

/**
 * @brief Returns the ucCode of the UC.
 * @details Time complexity: O(1)
 * @return ucCode code of the UC
 */

string Uc::getUcCode() const { return this->ucCode; }

/**
 * @brief Adds a new class to the classes
 * @details Time complexity: O(log(n))
 * @param newClass new class of the UC
 */

void Uc::addClass(const Class &newClass) {
    string newClassCode = newClass.getClassCode();
    this->classes[newClassCode] = {newClass};
}

/**
 * @brief Returns a class given a class code.
 * @details Time complexity: O(log(n))
 * @param classCode class code of the class to be returned
 * @return class with code == classCode
 */

Class &Uc::getClass(const string &classCode) {
    return this->classes.at(classCode);
}

/**
 * @brief Returns all the classes of UC.
 * @details Time complexity: O(1)
 * @return all the classes of the UC
 */

const map<string, Class> &Uc::getAllClasses() const { return this->classes; }

/*
 *@brief checks if a class exists in the uc
 *@details Time complexity: O(log(n))
 *@param classCode Code of the class to check
 *@return true If the class exists in the Uc, otherwise False
 */
bool Uc::hasClass(const string &classCode) const {
    return (classes.find(classCode) != classes.end());
}

/*
 *@brief checks if the Uc has vacancies
 *@details Time complexity: O(n)
 *@return True if the Uc has a class with vacancy, otherwise False
 */

bool Uc::hasVacancies() const {
    for (const auto &[classCode, c] : classes) {
        if (c.hasVacancies()) {
            return true;
        }
    }
    return false;
}

bool Uc::balancedClasses(const string &originClassCode,
                         const string &destinyClassCode) const {
    int maxSize = numeric_limits<int>::min();
    int minSize = numeric_limits<int>::max();
    float media = 0;
    for (const auto &[classCode, c] : classes) {
        int size = c.numberStudents();
        media += size;
        if (size > maxSize) {
            maxSize = size;
        } else if (size < minSize) {
            minSize = size;
        }
    }
    media /= classes.size();
    int originSize = originClassCode == ""
                         ? maxSize
                         : classes.at(originClassCode).numberStudents() - 1;
    int destinySize = destinyClassCode == ""
                          ? minSize
                          : classes.at(destinyClassCode).numberStudents() + 1;

    bool isBalanced = destinySize - originSize <= 4 &&
                      maxSize - originSize <= 4 && destinySize - minSize <= 4;
    bool betterBalanced = originSize >= media && destinySize <= media;
    return (isBalanced || betterBalanced);
}
