#ifndef PROJETO_APP_H
#define PROJETO_APP_H


#include "Data.h"
#include "UserInterface.h"

class App {
private:
    Data data;

public:
    App();
    void run();
    void handleMainMenu(); // prints menu and waits for user input and handles it.
    void handleMainMenuErrors(const string error); // prints error ( calls UserInteface::printError() ) and waits for user input to continue.
    //etc...
};


#endif //PROJETO_APP_H
