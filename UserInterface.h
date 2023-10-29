#ifndef PROJETO_USERINTERFACE_H
#define PROJETO_USERINTERFACE_H

#include <string>

using namespace std;

class UserInterface
{
public:
    static void printMainMenu();
    static char readInput(); // Returns the char that corresponds to the selected menu option
    static void printError(const string error);
    //etc...
};


#endif //PROJETO_USERINTERFACE_H
