#include "App.h"


App::App() {}

void App::run() {

}

void App::handleErrors(const string error) {
    UserInterface::printError(error);
}

void App::mainMenu() {
    UserInterface::printMainMenu();
    bool inputerror;
    do {
        inputerror= false;
        switch (UserInterface::readInput("Select an option: ")) {
            case '1':
                consult();
                break;
            case '2':
                newResquest();
                break;
            case '3':
                processRequest();
                break;
            default:
                handleErrors("Invalid Input");
                inputerror=true;
                break;
        }
    } while (inputerror);
}


void App::consult() {
    UserInterface::printConsult();
    bool inputerror;
    do { //escape key??
        inputerror= false;
        switch (UserInterface::readInput("Select an option: ")) {
            case '1':
                consultScheduleStudent();
                break;
            case '2':
                consultScheduleClass();
                break;
            case '3':
                consultStudentsClass();
                break;
            case '4':
                consultStudentsCourse();
                break;
            case '5':
                consultStudentsYear();
                break;
            case '6':
                consultNumStudentsUcs();
                break;
            case '7':
                consultClassYearUcOccupation();
                break;
            case '8':
                consultBiggestUc();
                break;
            case '9':
                mainMenu();
                break;
            default:
                handleErrors("Invalid Input");
                inputerror=true;
                break;
        }
    } while (inputerror);
}

void App::consultScheduleStudent() {
    char studentCode = UserInterface::readInput("Student Code: ");
    //data.consultScheduleStudent
}

void App::consultScheduleClass() {
    char classCode = UserInterface::readInput("Class Code: ");
    //data.consultSheduleClass
}

void App::consultStudentsClass() {
    char classCode = UserInterface::readInput("Class Code: ");
    //data.consultStudentsClass
}

void App::consultStudentsCourse() {
    char courseCode = UserInterface::readInput("Course Code: ");
    //data.consultStudentsCourse
}

void App::consultStudentsYear() {
    char year = UserInterface::readInput("Year: ");
    //data.consultStudentsYear()
}

void App::consultNumStudentsUcs() {
    char nUcs = UserInterface::readInput("Número de Ucs: ");
    //data.consultNumStudentsUcs
}

void App::consultClassYearUcOccupation() {   //o que significa
}

void App::consultBiggestUc() {
    //data.consultBiggestUc
}


void App::newResquest() {
    UserInterface::printNewRequest();
    bool inputerror;
    do {
        inputerror= false;
        switch (UserInterface::readInput("Select an option: ")) {
            case '1':
                newRequestAdd();
                break;
            case '2':
                newRequestRemove();
                break;
            case '3':
                newRequestSwitch();
                break;
            case '4':
                mainMenu();
                break;
            default:
                handleErrors("Invalid Input");
                inputerror=true;
                break;
        }
    } while (inputerror);

}

void App::newRequestAdd() {
    //falta implementar ligar edu
}

void App::newRequestRemove() {
    //falta implementar ligar edu
}

void App::newRequestSwitch() {
    //falta implementar ligar edu
}



void App::processRequest() {
    UserInterface::printProcessRequest();
    bool inputerror;
    do {
        inputerror= false;
        switch (UserInterface::readInput("Select an option: ")) {
            case '1':
                processPendingRequests();
                break;
            case '2':
                adminMenu();
                break;
            case '3':
                mainMenu();
                break;
            default:
                handleErrors("Invalid Input");
                inputerror=true;
                break;
        }
    } while (inputerror);
}

void App::processPendingRequests() {
    //falta implementar ligar edu
}

void App::adminMenu() {
    //falta implementat ligar edu
}


