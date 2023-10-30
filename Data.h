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
    map<int, Student> students;
    queue<Request> pedentRequests;
    forward_list<Request> requestHistory;

   public:
    // Data constructor
    Data();

    // ucs related methods
    map<string, Uc> getAllUcs() const;
    Uc &getUc(const string &ucCode);

    // students related methods
    map<int, Student> getAllStudents() const;
    Student &getStudent(int studentCode);

    // requests related methods
    void createRequest(int studentCode, std::string type,
                       std::string originCode, std::string destinyCode);
    void processRequests();

    bool verifyRequest(Request request);

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
