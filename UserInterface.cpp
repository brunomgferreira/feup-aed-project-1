#include <limits>
#include "UserInterface.h"



void UserInterface::printError(const string error) {
    cout << error << endl;
}

char UserInterface::readOption(const string msg) {
    char input;
    cout << endl << msg;
    cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
    //saltar linha depois cin
}

string UserInterface::readCode(const string msg) {
    string input;
    cout << endl << msg;
    cin >> input;
    return input;
    //saltar linha depois cin
}

int UserInterface::readNumber(const string msg) {
    int input;
    cout << endl << msg;
    cin >> input;
    return input;
    //saltar linha depois cin
}

void UserInterface::printMainMenu() {
    cout << endl;
    cout << "Main Menu" << endl;
    cout << "\n"
            "1 Consult\n"
            "2 New Request\n"
            "3 Process Request\n"
            "q Exit\n";
}


void UserInterface::printConsultMenu() {
    cout << endl;
    cout << "Consult Menu" << endl;
    cout << "\n"
            "1 Consult the schedule of a given student\n"
            "2 Consult the schedule of a given class\n"
            "3 Consult the students within a given class\n"
            "4 Consult the students within a given course\n"
            "5 Consult the students within a given year\n"
            "6 Consult the number of students registered in at least n UCs\n"
            "7 Consult the class/year/UC occupation (sorting by UC, ascending or descending order, …)\n"
            "8 Consult the UCs with the greatest number of students\n"
            "q Back to Main Menu\n";
}

void UserInterface::printTryAgainMenu() {
    cout << "\n"
            "1 Try again\n"
            "q Go back\n";
}

void UserInterface::pressEnterToContinue() {
    cout << "Press ENTER to continue... ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

void UserInterface::printNewRequestMenu() {
    cout << endl;
    cout << "New Request Menu" << endl;
    cout << "\n"
            "1 Add Request\n" //Nome request do tipo add nao add request??
            "2 Remove Request\n"
            "3 Switch Request\n"
            "q Back to Main Menu\n";
}

void UserInterface::printProcessRequestMenu() {
    cout << endl;
    cout << "Process Request Menu" << endl;
    cout << "\n"
            "1 Process Pending Requests\n"
            "3 See recent actions \n"
            "2 Undo recent actions \n"
            "q Back to Main Menu\n";
}









