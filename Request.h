

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

using namespace std;

struct Request {
    char type;
    string originClassCode;
    string destinyClassCode;
    string ucCode;
    intstring studentCode;

   public:
    Request(int studentCode, char type, const string& ucCode,
            const string& originClassCode, const string& destinyClassCode);
};

#endif
