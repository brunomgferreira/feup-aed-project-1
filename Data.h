#ifndef DATA_H
#define DATA_H

#include <map>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iostream>
#include "Data.h"
#include "Student.h"
#include "Uc.h"

/**
 * @brief Class that saves all the program data.
 */

class Data
{
private:
    map<string, Uc> ucs;
    map<int, Student> students;

public:
    // Data constructor
    Data();

    // ucs related methods
    map<string, Uc> getAllUcs() const;
    Uc &getUc(const string &ucCode);

    // students related methods
    map<int, Student> getAllStudents() const;
    Student &getStudent(int studentCode);

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