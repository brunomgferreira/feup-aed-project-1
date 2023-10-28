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

Uc::Uc(const string &ucCode)
{
    this->ucCode = ucCode;
}

/**
 * @brief Returns the ucCode of the UC.
 * @details Time complexity: O(1)
 * @return ucCode code of the UC
 */

string Uc::getUcCode() const
{
    return this->ucCode;
}

/**
 * @brief Adds a new class to the classes
 * @details Time complexity: O(log(n))
 * @param newClass new class of the UC
 */

void Uc::addClass(const Class &newClass)
{
    string newClassCode = newClass.getClassCode();
    this->classes[newClassCode] = {newClass};
}

/**
 * @brief Returns a class given a class code.
 * @details Time complexity: O(log(n))
 * @param classCode class code of the class to be returned
 * @return class with code == classCode
 */

Class &Uc::getClass(const string &classCode)
{
    return this->classes.at(classCode);
}

/**
 * @brief Returns all the classes of UC.
 * @details Time complexity: O(1)
 * @return all the classes of the UC
 */

const map<string, Class>& Uc::getAllClasses() const
{
    return this->classes;
}