#include "UserInterface.h"




void UserInterface::printError(const string error) {
    cout << error;
}


char UserInterface::readInput(const string msg) {
    char input;
    cout << msg;
    cin >> input;
    return input;
    //saltar linha depois cin
}


void UserInterface::printMainMenu() {
    cout << "Main Menu" << endl;
    cout << "1 Consult\n"
            "2 New Request\n"
            "3 Process Request\n";
}


void UserInterface::printConsult() {
    cout << "Consult Menu" << endl;
    cout << "1 Consult the schedule of a given student\n"
            "2 Consult the schedule of a given class\n"
            "3 Consult the students within a given class\n"
            "4 Consult the students within a given course\n"
            "5 Consult the students within a given year\n"
            "6 Consult the number of students registered in at least n UCs\n"
            "7 Consult the class/year/UC occupation (sorting by UC, ascending or descending order, …)\n"
            "8 Consult the UCs with the greatest number of students\n"
            "9 Back to Main Menu" << endl;
}

void UserInterface::printNewRequest() {
    cout << "New Request Menu" << endl;
    cout << "1 Add Request\n" //Nome request do tipo add nao add request??
            "2 Remove Request\n"
            "3 Switch Request\n"
            "4 Back to Main Menu" << endl;
}

void UserInterface::printProcessRequest() {
    cout << "Process Request Menu" << endl;
    cout << "1 Process Pending Requests\n"
            "2 ADMIN Menu - Undo recent actions \n"
            "3 Back to Main Menu" << endl;
}









