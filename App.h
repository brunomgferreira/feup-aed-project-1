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
    void mainMenu(); // prints menu and waits for user input and handles it.
    void handleErrors(const string error); // prints error ( calls UserInteface::printError() ) and waits for user input to continue.
    //etc...
    void consult();
    void newResquest();
    void processRequest();

    void consultScheduleStudent();
    void consultScheduleClass();
    void consultStudentsClass();
    void consultStudentsCourse();
    void consultStudentsYear();
    void consultNumStudentsUcs();
    void consultClassYearUcOccupation();
    void consultBiggestUc();

    void newRequestAdd();
    void newRequestRemove();
    void newRequestSwitch();

    void processPendingRequests();
    void adminMenu();

};


#endif //PROJETO_APP_H
