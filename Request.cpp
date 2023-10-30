

#include "Request.h"

Request::Request(int studentCode, const string& type, const string& originCode,
                 const string& destinyCode)
    : studentCode(studentCode),
      type(type),
      originClassCode(originCode),
      destinyClassCode(destinyCode) {}
