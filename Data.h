#ifndef DATA_H
#define DATA_H

#include <algorithm>
#include <forward_list>
#include <fstream>
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
    const string DIRECTORY_PATH = filesystem::current_path().string() + "/";

   private:
    map<string, Uc> ucs;
    unordered_map<string, set<string>> ucsCodesByClassCode;
    map<int, Student> students;
    queue<Request> pendentRequests;
    forward_list<Request> requestHistory;

   public:
    // Data constructor
    Data();

    // ucs related methods
    map<string, Uc> getAllUcs() const;
    Uc &getUc(const string &ucCode);

    set<string> getUcsByClassCode(const string &classCode) const;

    // students related methods
    map<int, Student> getAllStudents() const;
    Student &getStudent(int studentCode);
    bool studentExists(int studentCode);

    // requests related methods
    void createAddRequest(int studentCode, const string &ucCode,
                          const string &classCode);
    void createSwitchRequest(int studentCode, const string &ucCode,
                             const string &originClassCode,
                             const string &destinyClassCode);
    void createRemoveRequest(int studentCode, const string &ucCode);
    void processRequests();

    bool validRequest(const Request &request) const;
    void applyRequest(const Request &request);

    queue<Request> &getPendentRequests();
    forward_list<Request> &getRequestHistory();

    // Read and Write data
    void loadData();
    void saveData();

    // requests Pendent files
    void readPendentRequestsFile();
    void writePendentRequestsFile();

    // requests history file
    void readRequestHistoryFile();
    void writeRequestHistoryFile();

    // classes_per_uc.csv
    void readClassesPerUcFile();
    void writeClassesPerUcFile();

    // classes.csv
    void readClassesFile();
    void writeClassesFile();

    // students_classes.csv
    void readStudentsClassesFile();
    void writeStudentsClassesFile();
};

#endif
