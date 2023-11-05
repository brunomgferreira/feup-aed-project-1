

#ifndef REQUEST_H
#define REQUEST_H

#include <sstream>
#include <string>

using namespace std;

struct Request {
    char type;
    string originClassCode;
    string destinyClassCode;
    string ucCode;
    int studentCode;

   public:
    /**
 * @brief Constructs a Request object.
 *
 * @details Initializes a Request object with the provided parameters.
 *@details Time complexity: O(1)
 * @param studentCode The code of the student associated with the request.
 * @param type The type of the request ('A' for Add, 'R' for Remove, 'S' for Switch).
 * @param ucCode The code of the Unit Course (UC) involved in the request.
 * @param originClassCode The code of the class from which the student is moving
 *                       (used in Remove and Switch requests).
 * @param destinyClassCode The code of the class to which the student is moving
 *                        (used in Add and Switch requests).
     */
    Request(int studentCode, char type, string ucCode, string originClassCode,
            string destinyClassCode);
    /**
 * @brief Generates a string representing information about the request.
 *
 * @details This method creates a string containing information about the request, including the
 * request type, student code, and relevant UC and class codes.
 * @details Time complexity: O(1)
 *
 * @return A string with details about the request.
     */
    string stringInfo() const;
};

#endif
