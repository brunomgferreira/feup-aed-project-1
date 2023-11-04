

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

using namespace std;

struct Request {
    char type;
    string originClassCode;
    string destinyClassCode;
    string ucCode;
    int studentCode;

   public:
    Request(int studentCode, char type, string ucCode, string originClassCode,
            string destinyClassCode);
};

#endif
