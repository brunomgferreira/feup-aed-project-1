#ifndef UC_H
#define UC_H

#include <map>
#include "Class.h"
using namespace std;

/**
 * @brief Class that represents a UC. It saves all corresponding classes of a given UC.
 */

class Uc
{
private:
    string ucCode;
    // classCode -> class
    map<string, Class> classes;

public:
    // Uc constructor
    Uc();
    Uc(const string &ucCode);

    // Set & Getter -> ucCode
    string getUcCode() const;

    // classes related methods
    void addClass(const Class &newClass);
    Class &getClass(const string &classCode);
    const map<string, Class>& getAllClasses() const;
};

#endif