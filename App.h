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
    void close();
    void mainMenu(); // prints menu and waits for user input and handles it.
    bool tryAgainMenu();
    void handleErrors(const string& error); // prints error ( calls UserInteface::printError() ) and waits for user input to continue.
    void consultMenu();
    void newRequestMenu();
    void processRequestMenu();

    void consultStudentSchedule();
    void consultClassSchedule();
    //void consultClassStudentsGetUcCode();
    //void consultClassStudentsGetClassCode(const Uc& uc);
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

#endif  // PROJETO_APP_H
