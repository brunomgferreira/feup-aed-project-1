#include "App.h"
#include <iostream>

App::App() {}

void App::run() {
    ifstream inputFile1("/home/bruno/Documents/AED/projeto/schedule/classes_per_uc.csv");
    ifstream inputFile2("/home/bruno/Documents/AED/projeto/schedule/classes.csv");
    ifstream inputFile3("/home/bruno/Documents/AED/projeto/schedule/students_classes.csv");
    ifstream inputFile4("/home/bruno/Documents/AED/projeto/schedule/request_history.csv");

    this->data.readClassesPerUcFile(inputFile1);
    this->data.readClassesFile(inputFile2);
    this->data.readStudentsClassesFile(inputFile3);
    this->data.readRequestHistoryFile(inputFile4);

    inputFile1.close();
    inputFile2.close();
    inputFile3.close();
    inputFile4.close();

    mainMenu();
}

void App::close() {
    ofstream outputFile1("/home/bruno/Documents/AED/projeto/classes_per_uc.csv");
    ofstream outputFile2("/home/bruno/Documents/AED/projeto/classes.csv");
    ofstream outputFile3("/home/bruno/Documents/AED/projeto/students_classes.csv");
    ofstream outputFile4("/home/bruno/Documents/AED/projeto/schedule/request_history.csv");

    this->data.writeClassesPerUcFile(outputFile1);
    this->data.writeClassesFile(outputFile2);
    this->data.writeStudentsClassesFile(outputFile3);
    this->data.writeRequestHistoryFile(outputFile4);

    outputFile1.close();
    outputFile2.close();
    outputFile3.close();
    outputFile4.close();
}

void App::handleErrors(const string &error) {
    UserInterface::printError(error);
}

void App::mainMenu() {
    UserInterface::printMainMenu();
    bool shouldExit = false;
    bool inputError;
    do {
        inputError= false;
        switch (UserInterface::readOption("Select an option: ")) {
            case '1':
                consultMenu();
                break;
            case '2':
                newRequestMenu();
                break;
            case '3':
                processRequestMenu();
                break;
            case 'q':
                shouldExit = true;
                break;
            default:
                handleErrors("Invalid Input");
                inputError=true;
                break;
        }
    } while (inputError || !shouldExit);
}


void App::consultMenu() {
    UserInterface::printConsultMenu();
    bool shouldExit = false;
    bool inputError;
    do { //escape key??
        inputError= false;
        switch (UserInterface::readOption("Select an option: ")) {
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
            case 'q':
                shouldExit = true;
                break;
            default:
                handleErrors("Invalid Input");
                inputError=true;
                break;
        }
    } while (inputError || !shouldExit);

    UserInterface::printMainMenu();
}

bool App::tryAgainMenu() {
    bool shouldExit = false;
    bool inputError;
    do {
        inputError= false;
        UserInterface::printTryAgainMenu();
        switch (UserInterface::readOption("Select an option: ")) {
            case '1':
                break;
            case 'q':
                shouldExit = true;
                break;
            default:
                handleErrors("Invalid Input");
                inputError=true;
                break;
        }
    } while (inputError);

    return shouldExit;
}

void App::consultScheduleStudent() {
    bool shouldExit = false;

    while(!shouldExit) {
        try {
            int studentCode = stoi(UserInterface::readCode("Student Code: "));
            Student student = data.getStudent(studentCode);
            UserInterface::printStudentSchedule(student);
            UserInterface::pressEnterToContinue();
            break;
        }
        catch (const out_of_range& e) {
            handleErrors("This student doesn't exist in the database.");
            shouldExit = tryAgainMenu();
        }
        catch (const invalid_argument& e) {
            handleErrors("Invalid student code. Please ensure the student code consists of numeric digits only.");
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}

void App::consultScheduleClass() {
    string classCode = UserInterface::readCode("Class Code: ");
    //data.consultSheduleClass
}

void App::consultStudentsClass() {
    string classCode = UserInterface::readCode("Class Code: ");
    //data.consultStudentsClass
}

void App::consultStudentsCourse() {
    string courseCode = UserInterface::readCode("Course Code: ");
    //data.consultStudentsCourse
}

void App::consultStudentsYear() {
    int year = UserInterface::readNumber("Year: ");
    //data.consultStudentsYear()
}

void App::consultNumStudentsUcs() {
    int nUcs = UserInterface::readNumber("Número de Ucs: ");
    //data.consultNumStudentsUcs
}

void App::consultClassYearUcOccupation() {   //o que significa
}

void App::consultBiggestUc() {
    //data.consultBiggestUc
}


void App::newRequestMenu() {
    UserInterface::printNewRequestMenu();
    bool shouldExit = false;
    bool inputError;
    do {
        inputError= false;
        switch (UserInterface::readOption("Select an option: ")) {
            case '1':
                newRequestAdd();
                break;
            case '2':
                newRequestRemove();
                break;
            case '3':
                newRequestSwitch();
                break;
            case 'q':
                shouldExit=true;
                break;
            default:
                handleErrors("Invalid Input");
                inputError=true;
                break;
        }
    } while (inputError || !shouldExit);

    UserInterface::printMainMenu();
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



void App::processRequestMenu() {
    UserInterface::printProcessRequestMenu();
    bool shouldExit;
    bool inputError;
    do {
        inputError= false;
        switch (UserInterface::readOption("Select an option: ")) {
            case '1':
                processPendingRequests();
                break;
            case '2':
                adminMenu();
                break;
            case 'q':
                shouldExit=true;
                break;
            default:
                handleErrors("Invalid Input");
                inputError=true;
                break;
        }
    } while (inputError || !shouldExit);

    UserInterface::printMainMenu();
}

void App::processPendingRequests() {
    //falta implementar ligar edu
}

void App::adminMenu() {
    //falta implementat ligar edu
}


