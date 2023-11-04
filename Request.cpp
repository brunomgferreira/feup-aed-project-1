

#include "Request.h"

#include <sstream>
#include <string>

Request::Request(int studentCode, char type, string ucCode,
                 string originClassCode, string destinyClassCode)
    : studentCode(studentCode),
      type(type),
      ucCode(ucCode),
      originClassCode(originClassCode),
      destinyClassCode(destinyClassCode) {}

string Request::stringInfo() const {
    stringstream info;
    switch (type) {
        case 'A':
            info << "Add Request - Student: " << studentCode << '\n';
            info << "Joined Uc: " << ucCode
                 << ". In class: " << destinyClassCode << '\n';
            break;
        case 'R':
            info << "Remove Request - Student: " << studentCode << '\n';
            info << "Exited Uc: " << ucCode
                 << ". Leaving the class: " << originClassCode << '\n';
            break;
        case 'S':
            info << "Switch Request - Student: " << studentCode << '\n';
            info << "In Uc: " << ucCode << ". Exited: " << originClassCode
                 << ". Joined: " << destinyClassCode << '\n';
            break;
    }
    return info.str();
}
