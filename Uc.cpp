#include "Uc.h"



Uc::Uc() {}


Uc::Uc(const string &ucCode) { this->ucCode = ucCode; }


void Uc::addClass(const Class &newClass) {
    string newClassCode = newClass.getClassCode();
    this->classes[newClassCode] = {newClass};
}


 Class &Uc::getClass(const string &classCode) {
    return this->classes.at(classCode);
}


const map<string, Class> &Uc::getAllClasses() const { return this->classes; }


bool Uc::hasClass(const string &classCode) const {
    return (classes.find(classCode) != classes.end());
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
