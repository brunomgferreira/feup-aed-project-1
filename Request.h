

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

using namespace std;

struct Request {
   private:
    std::string type;
    std::string originClassCode;
    std::string destinyClassCode;
    int studentCode;

   public:
    Request(int studentCode, const string& type, const string& originCode,
            const string& destinyCode);
};

#endif
