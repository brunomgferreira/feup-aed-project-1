

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

struct Request {
   private:
    std::string type;
    std::string originClassCode;
    std::string destinyClassCode;
    int studentCode;

   public:
    Request(int studentCode, std::string type, std::string originCode,
            std::string destinyCode);
};

#endif
