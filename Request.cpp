

#include "Request.h"

Request::Request(int studentCode, char type, const string& ucCode,
                 const string& originClassCode, const string& destinyClassCode)
    : studentCode(studentCode),
      type(type),
      ucCode(ucCode),
      originClassCode(originClassCode),
      destinyClassCode(destinyClassCode) {}
