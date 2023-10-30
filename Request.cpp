

#include "Request.h"

Request::Request(int studentCode, std::string type, std::string originCode,
                 std::string destinyCode)
    : studentCode(studentCode),
      type(type),
      originClassCode(originCode),
      destinyClassCode(destinyCode) {}
