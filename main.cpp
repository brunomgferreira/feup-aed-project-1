#include <iostream>
#include <fstream>
// #include "readClassesPerUcFile.h"
// #include "readClassesFile.h"
// #include "readStudentsClassesFile.h"
#include "Data.h"
#include <filesystem>
using namespace std;

int main()
{
    ifstream inputFile1("/home/bruno/Documents/AED/projeto/schedule/classes_per_uc.csv");
    ifstream inputFile2("/home/bruno/Documents/AED/projeto/schedule/classes.csv");
    ifstream inputFile3("/home/bruno/Documents/AED/projeto/schedule/students_classes.csv");

    ofstream outputFile1("/home/bruno/Documents/AED/projeto/classes_per_uc.csv");
    ofstream outputFile2("/home/bruno/Documents/AED/projeto/classes.csv");
    ofstream outputFile3("/home/bruno/Documents/AED/projeto/students_classes.csv");

    Data data;

    data.readClassesPerUcFile(inputFile1);
    data.readClassesFile(inputFile2);
    data.readStudentsClassesFile(inputFile3);

    data.writeClassesPerUcFile(outputFile1);
    data.writeClassesFile(outputFile2);
    data.writeStudentsClassesFile(outputFile3);

    // map<string, Uc> ucs;
    // map<int, Student> students;
    // multimap<string, int> studentsNameToCode;

    // readClassesPerUcFile(ucs, inputFile1);
    // readClassesFile(ucs, inputFile2);
    // readStudentsClassesFile(ucs, students, studentsNameToCode, inputFile3);
    // std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    // for (const auto &[ucCode, uc] : ucs)
    // {
    //     cout << ucCode << endl;

    //     for (const auto &[classCode, c] : uc.getAllClasses())
    //     {
    //         cout << c.getClassCode() << ": ";

    //         for (const ClassSchedule &schedule : c.getAllClassSchedules())
    //         {
    //             cout << schedule.getWeekday() << "-" << schedule.getTimeInterval().getTimeIntervalAsString() << "-" << schedule.getType() << " ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    // cout << students.size() << endl;
    // cout << studentsNameToCode.size() << endl;
    // for (const auto &[studentCode, student] : students)
    // {
    //     cout << studentCode << ": ";

    //     for (const auto &[ucCode, studentClass] : student.getAllClasses())
    //     {
    //         cout << studentClass.getClassCode() << ": ";

    //         for (const ClassSchedule &schedule : studentClass.getAllClassSchedules())
    //         {
    //             cout << schedule.getWeekday() << "-" << schedule.getTimeInterval().getTimeIntervalAsString() << "-" << schedule.getType() << " ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    // for (const auto &[studentName, studentCode] : studentsNameToCode)
    // {
    //     cout << studentName << " " << studentCode << endl;
    // }

    return 0;
}