#ifndef DATA_H
#define DATA_H

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>

#include "Data.h"
#include "Request.h"
#include "Student.h"
#include "Uc.h"
#include "filesystem"

/**
 * @brief Class that saves all the program data.
 */
class Data {
   private:
    const string CLASSES_FILENAME = "classes.csv";
    const string CLASSES_PER_UC_FILENAME = "classes_per_uc.csv";
    const string REQUESTS_HISTORY_FILENAME = "request_history.csv";
    const string PENDENT_REQUESTS_FILENAME = "pendent_requests.csv";
    const string STUDENTS_CLASS_FILENAME = "students_classes.csv";
    const string DIRECTORY_PATH =
        "/home/soestilooo/Documents/Faculty/AED/project/schedule/";


   private:
    map<string, Uc> ucs;
    unordered_map<string, set<string>> ucsCodesByClassCode;
    map<int, Student> students;
    queue<Request> pendentRequests;
    list<Request> requestHistory;

   private:
    /**
 * @brief Checks if a string consists of only numeric characters.
 *
 * @details This function iterates through each character in the provided string 'str'
 * and checks if every character is a numeric digit (0-9). It returns true if
 * all characters in the string are numeric, indicating that the string is numeric.
 * @details Time complexity: O(n)
 *
 * @param str A string to check for numeric content.
 *
 * @return true if the string consists of numeric characters only; otherwise, false.
     */
    static bool isNumeric(const string &str);

   public:
    // Data constructor
    /**
 * @brief Default constructor for the Data class.
 *
 * @details This default constructor creates a new instance of the Data class without
 * specifying any initial values. It initializes the Data object with default values.
     * @details Time complexity: O(1)
     */
    Data();

    // UC related methods
    /**
 * @brief Retrieves all Unit Courses (UCs) in the Data (const version).
 *
 * @details This const method returns a reference to the map containing all the Unit Courses (UCs)
 * present in the Data. The map is keyed by the UC code and contains Uc objects. This const version
 * allows read-only access to the UC data.
     * @details Time complexity: O(1)
 *
 * @return A const reference to the map where the keys are UC codes, and the values are Uc objects.
     */
    map<string, Uc> getAllUcs() const;
    /**
 * @brief Retrieves a Unit Course (UC) by its UC code.
 *
 * @details This method retrieves a specific Unit Course (UC) from the Data by its UC code.
 * If a matching UC with the provided code is found, a reference to that UC is returned.
 * @details Time complexity: O(log n)
 *
 * @param ucCode A string representing the UC code of the UC to retrieve.
 *
 * @return A reference to the Unit Course (UC) with the specified UC code.
     */
    Uc &getUc(const string &ucCode);
    /**
 * @brief Checks if a Unit Course (UC) exists in the Data.
 *
 * @details This method checks if a Unit Course (UC) with the specified UC code exists in the Data.
 * It iterates through the existing UCs and returns true if a matching UC is found.
     * @details Time complexity: O(n)
 *
 * @param ucCode A string representing the UC code to check for existence.
 *
 * @return true if a Unit Course with the specified UC code exists in the Data; otherwise, false.
     */
    bool ucExists(const string &ucCode);
    // Consult related methods
    /**
 * @brief Consults and retrieves information about students in a specific Class.
 *
 * @details This method consults and retrieves information about students who are enrolled in
 * a specific Class within a Unit Course (UC). It checks if the UC and Class exist in the Data
 * and then compiles information about the students, including student code, name, and enrolled UCs.
 * @details Time complexity: O(N), where N is the number of students in the specified class.
     *
 * @param ucCode A string representing the UC (Unit Course) code.
 * @param classCode A string representing the Class code.
 *
 * @return A formatted string with information about the students in the specified Class.
 * @throws std::invalid_argument if the UC or Class does not exist in the database.
     */
    string consultStudentsClass(const string &ucCode, const string &classCode);
    /**
 * @brief Consults and retrieves information about students in all Classes of a specific Unit Course (UC).
 *
 * @details This method consults and retrieves information about students who are enrolled in all Classes of a
 * specific Unit Course (UC). It checks if the UC exists in the Data and then compiles information about
 * the students in each Class, including student code, name, and enrolled UCs.
 * @details Time complexity: O(M * N) where M is the number of classes and N is the average number of students in each class.
 *
 * @param ucCode A string representing the UC (Unit Course) code.
 *
 * @return A formatted string with information about the students in all Classes of the specified UC.
 * @throws std::invalid_argument if the UC does not exist in the database.
     */
    string consultStudentsCourse(const string &ucCode);
    /**
 * @brief Consults and retrieves information about students in a specific academic year.
 *
 * @details This method consults and retrieves information about students who are enrolled in Unit Courses
 * and Classes corresponding to a specific academic year. It checks if the academic year is numeric
 * and within the valid range. Then, it compiles information about the students, including student code,
 * name, and enrolled UCs.
 * @details Time complexity: O(M * N * S), where M is the number of Unit Courses (UCs),
* N is the average number of classes in each UC for the specified academic year,
* and S is the average number of students in each Class.
 *
 * @param year A string representing the academic year (e.g., "1", "2", "3").
 *
 * @return A formatted string with information about the students in the specified academic year.
 * @throws std::invalid_argument if the year is not numeric or is out of range.
     */
    string consultStudentsYear(const string &year);
    /**
 * @brief Consults and retrieves information about the occupation of a specific Class.
 *
 * @details This method consults and retrieves information about the occupation of a specific Class within a Unit Course (UC).
 * It checks if the UC and Class exist in the Data and then compiles information about the number of students
 * and the number of vacancies in the Class.
 * @details Time complexity: O(log n).
 *
 * @param ucCode A string representing the UC (Unit Course) code.
 * @param classCode A string representing the Class code.
 *
 * @return A formatted string with information about the occupation of the specified Class.
 * @throws std::invalid_argument if the UC or Class does not exist in the database.
     */
    string consultOccupationClass(const string &ucCode, const string &classCode);
    /**
 * @brief Consults and retrieves information about the occupation of all Classes within a specific Unit Course (UC).
 *
 * @details This method consults and retrieves information about the occupation of all Classes within a specific Unit Course (UC).
 * It checks if the UC exists in the Data and then compiles information about the total number of students
 * and total number of vacancies across all Classes in the UC.
 * @details Time complexity: O(N), where N is the total number of classes in the specified UC.
 *
 * @param ucCode A string representing the UC (Unit Course) code.
 *
 * @return A formatted string with information about the occupation of all Classes in the specified UC.
 * @throws std::invalid_argument if the UC does not exist in the database.
     */
    string consultOccupationCourse(const string &ucCode);
    /**
 * @brief Consults and retrieves information about the occupation of students in a specific academic year.
 *
 * @details This method consults and retrieves information about the occupation of students who belong to
 * Unit Courses and Classes corresponding to a specific academic year. It checks if the academic year is numeric
 * and within the valid range, and then compiles information about the total number of students in that year.
 * @details Time complexity: O(M * N * S), where M is the number of Unit Courses (UCs),
 * N is the average number of classes in each UC for the specified academic year, and
 * S is the average number of students in each Class.
 *
 * @param year A string representing the academic year (e.g., "1", "2", "3").
 *
 * @return A formatted string with information about the occupation of students in the specified academic year.
 * @throws std::invalid_argument if the year is not numeric or is out of range.
     */
    string consultOccupationYear(const string &year);
    /**
 * @brief Consults and retrieves information about students registered in at least a specified number of Unit Courses (UCs).
 *
 * @details This method consults and retrieves information about students who are registered in at least a specified number of Unit Courses (UCs).
 * It checks if the input value is numeric and within the valid range, and then compiles information about the number of students meeting the criteria.
 * @details Time complexity: O(N), where N is the number of students in the database
 *
 * @param nUcs A string representing the minimum number of UCs a student should be registered in.
 *
 * @return A formatted string with information about the number of students registered in at least the specified number of UCs.
 * @throws std::invalid_argument if the input value is not numeric or is out of range.
     */
    string consultNumStudentsUcs(const string &nUcs);
    /**
 * @brief Consults and retrieves information about the Unit Courses (UCs) with the
  * most or least students.
 *
 * @details This method consults and retrieves information about the Unit Courses (UCs)
     * based on the total number of students in each UC.
     * It can sort the UCs in ascending or descending order of student count.
     * It first collects data about the total number of students in each UC,
     * then sorts the UCs based on the total student count using a custom sorting function,
     * and finally formats the results.
 * @details Time complexity: O(M * N), where M is the number of UCs,
 * and N is the average number of classes in each UC.
*
 * @param ascendingOrder A boolean flag indicating whether to sort the UCs in ascending (true) or descending (false) order.
 *
 * @return A formatted string with information about the UCs and their student counts.
     */
    string consultBiggestUc(bool ascendingOrder);
    /**
 * @brief Retrieves a set of Unit Course (UC) codes associated with a specific class code.
 *
 * @details This method retrieves a set of Unit Course (UC) codes associated with
     * a specific class code. It performs a constant-time lookup in the data structure,
     * making it an efficient operation.
 * @details Time complexity: O(log N) where N is the number of different classes that exist.
*
 * @param classCode A string representing the class code.
 *
 * @return A set of UC codes associated with the specified class code.
 * @throws std::out_of_range if the class code does not exist in the database.
     */
    set<string> getUcsByClassCode(const string &classCode) const;
    /**
 * @brief Checks if a class with a specific code exists within a Unit Course (UC).
 *
 * @details This method checks if a class with a specific code exists within a Unit Course (UC)
     * by performing an efficient lookup operation. It ensures that the class code is present within the UC, making it an efficient operation with a time complexity of O(log N) for data structures that support efficient searching.
 * @details Time complexity: O(log N), where N is the number of classes in the specified UC.
*
 * @param ucCode A string representing the UC (Unit Course) code.
 * @param classCode A string representing the class code.
 *
 * @return true if the class exists in the specified UC, false otherwise.
     */
    bool classExists(const string &ucCode, const string &classCode);

    // Students related methods
    map<int, Student> getAllStudents() const;
    /**
 * @brief Retrieves a reference to a specific student by their unique student code.
 *
 * @details This method retrieves a reference to a specific student in the database by their unique student code. It performs a constant-time lookup in the data structure, making it an efficient operation.
 * @details Time complexity: O(log N) where N is the total number of students.
*
 * @param studentCode An integer representing the unique student code.
 *
 * @return A reference to the specified student.
     */
    Student &getStudent(int studentCode);
    /**
 * @brief Checks if a student with a specific student code exists in the database.
 *
 * @details This method checks if a student with a specific student code exists in the database. It performs a constant-time lookup using the `std::unordered_map` data structure, making it an efficient operation.
 * @details Time complexity: O(log N) where N is the total number of students.
*
 * @param studentCode An integer representing the unique student code.
 *
 * @return true if the student with the specified code exists in the database, false otherwise.
     */
    bool studentExists(int studentCode);

    // Request related methods
    /**
 * @brief Creates an "Add" request for a student to join a specific Unit Course class.
 *
 * @details This method creates an "Add" request for a student to join a specific
     * Unit Course (UC) class. It performs several validation checks to ensure
     * that the request is valid, including checking if the student code is numeric,
     * if the UC and class exist, and if the student is not already enrolled in the UC.
     * After passing the checks, a new request is created and added to the list of
     * pending requests.
 * @details Time complexity: O(N + log M + log S) where N is the size of studentCode, M
     * the total number of UCs and S the total number of students.
*
 * @param studentCode A string representing the student's code.
 * @param ucCode A string representing the Unit Course code.
 * @param destinyClassCode A string representing the code of the class the student wants to join.
 *
 * @throws std::invalid_argument if any of the validation checks fail.
     */
    void createAddRequest(const string &studentCode, const string &ucCode,
                          const string &destinyclassCode);
    /**
 * @brief Creates a "Remove" request for a student to exit a specific Unit Course class.
 *

 * @details This method creates a "Remove" request for a student to exit a
     * specific Unit Course (UC) class. It performs several validation
     * checks to ensure that the request is valid, including checking if
     * the student code is numeric, if the student and UC exist,
     * and if the student is enrolled in the UC. After passing the checks,
     * a new request is created and added to the list of pending requests.
 * @details Time complexity: O(N + log S * log M) where N is the size of studentCode,
     * M is the total UCs the student is enrolled in, and S is the total number of students.
*
 * @param studentCode A string representing the student's code.
 * @param ucCode A string representing the Unit Course code.
 *
 * @throws std::invalid_argument if any of the validation checks fail.
     */
    void createRemoveRequest(const string &studentCode, const string &ucCode);
    /**
 * @brief Creates a "Switch" request for a student to change classes within a Unit Course.
 *
 * This method creates a "Switch" request for a student to change classes
     * within a specific Unit Course (UC). It performs validation checks to ensure the
     * request is valid, including checking if the student code is numeric,
     * if the student exists, if the UC exists, and if the destination class exists.
     * After passing the checks, a new request is created and added to the list of pending
     * requests, specifying the student's current class and the class they want to switch to.
 *@details Time complexity: O(N + log S * log M) where N is the size of studentCode,
* M is the total UCs the student is enrolled in, and S is the total number of students.
     *
 * @param studentCode A string representing the student's code.
 * @param ucCode A string representing the Unit Course code.
 * @param destinyClassCode A string representing the code of the class the student wants to switch to.
 *
     */
    void createSwitchRequest(const string &studentCode, const string &ucCode,
                             const string &destinyClassCode);
    /**
 * @brief Processes pending requests and provides a summary of the results.
 *
 * @details This method processes pending requests and provides a summary of the results.
     * It iterates through the pending requests queue, validates each request,
     * and applies successful requests to make schedule changes.
     * The method logs each request and its validation result.
*
 * @return A string summarizing the processing results, including the total number of requests processed and the number of successfully accepted requests.
     */
    string processRequests();
    /**
 * @brief Undoes a previous request and provides a summary of the undo operation.
 *

 * @details This method undoes a previous request and provides a summary of the undo operation.
     * It requires specifying the request number to undo.
     * The method validates the undo operation and, if successful, applies the undo action.
*
 * @param requestNumber A string representing the request number to undo.
 * @return A string summarizing the undo operation's status and result.
 *
 * @throws std::invalid_argument if the request number is not numeric or is not a valid request number.
     */
    string undoRequest(const string& requestNumber);
    /**
 * @brief Validates a request for schedule changes and provides a status message.
 *

 * @details This method validates a request for schedule changes and provides a status message
     * indicating whether the request is accepted or not. It performs various checks,
     * including ensuring the operation doesn't affect class balance,
     * verifying class vacancies, student enrollment limits, and schedule conflicts.
*
 * @param request A reference to the Request object representing the schedule change request.
 * @return A string message indicating whether the request is "Successful"
     * or contains information about why the request is not accepted.
     */
    string validRequest(const Request &request) const;
    /**
 * @brief Applies a schedule change request, including undoing requests if specified.
 *

 * @details This method applies a schedule change request, adding it to the
     * request history if its not an undo request.
     * It handles operations related to adding, removing, and switching classes for a student.
 * @details Time complexity: O(log S + log N * log M), where S is the total number of students,
     * N is the total number of UCs and M the average number of classes per UC .
*
 * @param request A reference to the Request object representing the schedule change request.
 * @param undo A boolean flag indicating whether to undo the request if set to true.
     */
    void applyRequest(const Request &request, bool undo);

    /**
 * @brief Retrieves the request history, providing a summary of past requests.
 *
 * @details This method retrieves the request history, which contains a summary of past schedule change requests.
     * It provides information about the type of request and relevant details for each request in the history.
 * @details Time complexity: O(N), where N is the number of requests in the request history.
*
 * @return A string containing the request history summary, or a message indicating an empty
     * request history if there are no past requests.
     */
    string getRequestHistory() const;

    // Read and Write data
    /**
 * @brief Loads data from external files to populate the database.
 *
 * @details This method loads data from external files to populate the database.
     * It reads data related to unit courses, classes, student enrollments,
     * request history, and pending requests.
     */
    void loadData();
    /**
 * @brief Saves the current database data to external files.
 *
 * @details This method saves the current database data to external files,
     * ensuring that the most up-to-date information is preserved.
     * It writes data related to unit courses, classes, student enrollments,
     * request history, and pending requests.
     */
    void saveData();

    // requests Pendent files
    /**
 * @brief Reads and populates the list of pending requests from an external file.
 *
  * @details This method reads data from an external file containing pending requests
     * and populates the list of pending requests in the database.
     * Each pending request represents a potential change in a student's class enrollment.
 * @details Time complexity: O(N), where N is the number of pending requests read from the file.
     */
    void readPendentRequestsFile();
    /**
 * @brief Writes the list of pending requests to an external file.
 *
  * @details This method writes the list of pending requests to an external file,
     * allowing the preservation of these requests for future processing.
     * Each pending request represents a potential change in a student's class enrollment.
 * @details Time complexity: O(N), where N is the number of pending requests in the list.
 *
     */
    void writePendentRequestsFile();

    // requests history file
    /**
 * @brief Reads the request history from an external file and populates the request history list.
 *
  * @details This method reads the request history from an external file and populates
     * the request history list. Each line in the file represents a past request or
     * operation that has been successfully processed.
 * @details Time complexity: O(N), where N is the number of requests in the history file.
 *
     */
    void readRequestHistoryFile();
    /**
 * @brief Writes the request history to an external file.
 *
 * @details This method writes the request history to an external file,
     * preserving the record of past requests and changes in class enrollment.
     * Each request in the history represents a past operation that has been successfully
     * processed.
 * @details Time complexity: O(N), where N is the number of requests in the history.
 *
     */
    void writeRequestHistoryFile();

    // classes_per_uc.csv
    /**
 * @brief Reads class assignments per Unit Course from an external file and populates the data structures.
 *
  * @details This method reads class assignments per Unit Course from an external file
     * and populates the relevant data structures. Each line in the file represents an
     * assignment of a class to a Unit Course. It first parses the data from the file and
     * then assigns classes to the appropriate UCs.
 * @details Time complexity: O(n * (log(m) + log(k))), where n is the number of lines in the file,
     * m is the number of Unit Courses (UCs), and k is the average number of classes per UC.
 *
     */
    void readClassesPerUcFile();
    /**
 * @brief Writes class assignments per Unit Course to an external file.
 *
  * @details This method writes class assignments per Unit Course to an external file.
     * It iterates through all the UCs and their associated classes, writing each
     * assignment to the file in a CSV format.
 * @details Time complexity: O(n * m), where n is the number of Unit Courses (UCs) and m is the average number of classes per UC.
 *
     */
    void writeClassesPerUcFile();

    // classes.csv
    /**
 * @brief Reads class information from an external file and populates the data structures.
 *
  * @details This method reads class information from an external file, parses the data,
     * and populates the data structures. It iterates through each line in the file,
     * parsing class information, and adding class schedules to the corresponding UC and class.
 * @details Time complexity: O(n * (log(k) + log(v))), where n is the number of classes, k is the number of Unit Courses (UCs), and v is the number of classes per UC on average.
 *
     */
    void readClassesFile();
    /**
 * @brief Writes class information to an external file based on the data structures.
 *
  * @details This method writes class information to an external file, including class codes,
     * UC codes, weekdays, start hours, durations, and types for each class schedule.
     * It iterates through the UCs, classes, and class schedules in the data structures to
     * create the output file.
 * @details Time complexity: O(n * m * k), where n is the number of classes, m is the average
     * number of classes per UC, and k is the average number of class schedules per class.
 *
     */
    void writeClassesFile();

    // students_classes.csv
    /**
 * @brief Reads student and class information from an external file and updates the data structures.
 *
  * @details This method reads student and class information from an external file,
     * updates the data structures with the extracted data, and handles the associations
     * between students and classes. It iterates through the file entries and processes
     * each entry to populate the data structures.
 * @details Time complexity: O(n * m * p * k * log(s) * log(u) * r), where n is the number
     * of entries in the file, m is the average number of characters per entry,
     * p is the number of classes per student, k is the average number of classes per UC,
     * s is the number of students, u is the number of UCs, and r is the length of the student
     * names.
 *
     */
    void readStudentsClassesFile();
    /**
 * @brief Writes student and class information to an external file.
 *
  * @details This method writes student and class information to an external file,
     * including student codes, names, UC codes, and class codes. It iterates through the
     * students and their associated classes, writing the data to the file.
 * @details Time complexity: O(n * m * p), where n is the number of students, m is the average number of classes per student, and p is the number of characters in student names.
 *
     */
    void writeStudentsClassesFile();
};

#endif
