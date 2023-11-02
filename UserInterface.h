#ifndef PROJETO_USERINTERFACE_H
#define PROJETO_USERINTERFACE_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Student.h"

using namespace std;

class UserInterface
{
public:
    static void printMainMenu();
    static char readOption(const string msg); // Returns the char that corresponds to the selected menu option
    static string readCode(const string msg);
    static int readNumber(const string msg);
    static void printError(const string error);
    static void printStudentSchedule(const Student& student);
    static void pressEnterToContinue();
    static void printConsultMenu();
    static void printTryAgainMenu();
    static void printNewRequestMenu();
    static void printProcessRequestMenu();

};


#endif //PROJETO_USERINTERFACE_H
