#ifndef DATA_H
#define DATA_H

#include <algorithm>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <string>

#include "Data.h"
#include "Request.h"
#include "Student.h"
#include "Uc.h"
/**
 * @brief Class that saves all the program data.
 */

class Data {
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
    string consultStudentsClass(const string &ucCode, const string &classCode);
    string consultStudentsCourse(const string &courseCode);
    string consultStudentsYear(int year);
    string consultNumStudentsUcs(int &nUcs);
    string consultBiggestUc();

    set<string> getUcsByClassCode(const string& classCode) const;

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
    void applyRequest(Request request);

    queue<Request> &getPendentRequests();
    forward_list<Request> &getRequestHistory();

    // requests history file
    void readRequestHistoryFile(ifstream &file);
    void writeRequestHistoryFile(ofstream &file);

    // classes_per_uc.csv
    void readClassesPerUcFile(ifstream &file);
    void writeClassesPerUcFile(ofstream &file);

    // classes.csv
    void readClassesFile(ifstream &file);
    void writeClassesFile(ofstream &file);

    // students_classes.csv
    void readStudentsClassesFile(ifstream &file);
    void writeStudentsClassesFile(ofstream &file);
};

#endif
