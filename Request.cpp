

#include "Request.h"

Request::Request(int studentCode, char type, string ucCode,
                 string originClassCode, string destinyClassCode)
    : studentCode(studentCode),
      type(type),
      ucCode(ucCode),
      originClassCode(originClassCode),
      destinyClassCode(destinyClassCode) {}
