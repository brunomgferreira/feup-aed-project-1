#ifndef PROJETO_USERINTERFACE_H
#define PROJETO_USERINTERFACE_H

#include <string>
#include <iostream>

using namespace std;

class UserInterface
{
public:
    static void printMainMenu();
    static char readInput(const string msg); // Returns the char that corresponds to the selected menu option
    static void printError(const string error);
    //etc...
    static void printConsult();
    static void printNewRequest();
    static void printProcessRequest();

};


#endif //PROJETO_USERINTERFACE_H
