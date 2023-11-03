#include "App.h"
#include <iostream>

App::App() {}

void App::run() {
    ifstream inputFile1("/home/xavier/Desktop/AED/Projeto/feup-aed-project-1/schedule/classes_per_uc.csv");
    ifstream inputFile2("/home/xavier/Desktop/AED/Projeto/feup-aed-project-1/schedule/classes.csv");
    ifstream inputFile3("/home/xavier/Desktop/AED/Projeto/feup-aed-project-1/schedule/students_classes.csv");
    ifstream inputFile4("/home/xavier/Desktop/AED/Projeto/feup-aed-project-1/schedule/request_history.csv");

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
    ofstream outputFile1("/home/xavier/Desktop/AED/Projeto/feup-aed-project-1/classes_per_uc.csv");
    ofstream outputFile2("/home/xavier/Desktop/AED/Projeto/feup-aed-project-1/classes.csv");
    ofstream outputFile3("/home/xavier/Desktop/AED/Projeto/feup-aed-project-1/students_classes.csv");
    ofstream outputFile4("/home/xavier/Desktop/AED/Projeto/feup-aed-project-1/schedule/request_history.csv");

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
                consultStudentSchedule();
                break;
            case '2':
                consultClassSchedule();
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

void App::consultStudentSchedule() {
    bool shouldExit = false;

    while(!shouldExit) {
        try {
            int studentCode = stoi(UserInterface::readCode("Student Code (i.e.: 123456789): "));
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

void App::consultClassSchedule() { //fazer aassimm ou mensagem com textos
    bool shouldExit = false;

    while(!shouldExit) {
        try {
            string classCode = UserInterface::readCode("Insert the Class Code (i.e.: 1LEIC01): ");
            set<string> ucs = data.getUcsByClassCode(classCode);

            unordered_map<string, int> weekdayToWeekdayNumberMap = {
                    {"Monday", 0},
                    {"Tuesday", 1},
                    {"Wednesday", 2},
                    {"Thursday", 3},
                    {"Friday", 4}
            };

            map<int,set<string>> schedulesByDay;
            for(const string& ucCode : ucs) {
                Class c = data.getAllUcs().at(ucCode).getClass(classCode);
                for(const ClassSchedule &classSchedule : c.getAllClassSchedules()) {
                    string ss =  classSchedule.getTimeInterval().getTimeIntervalAsString() + " "
                                 + c.getUcCode() + " (" + classSchedule.getType() + ")";

                    schedulesByDay[weekdayToWeekdayNumberMap.at(classSchedule.getWeekday())].insert(ss);
                }
            }
            UserInterface::printClassSchedule(classCode, ucs, schedulesByDay);
            UserInterface::pressEnterToContinue();
            break;
        }
        catch (const out_of_range& e) {
            handleErrors("This class doesn't exist in the database.");
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}


void App::consultStudentsClass() { //errors
    bool shouldExit = false;

    while(!shouldExit) {
        try {
            string ucCode = UserInterface::readCode("Insert the UC code (i.e.: L.EIC001): ");
            string classCode = UserInterface::readCode("Insert the Class Code (i.e.: 1LEIC01): ");
            string msg = data.consultStudentsClass(ucCode,classCode);
            UserInterface::printMessage(msg);
            UserInterface::pressEnterToContinue();
            break;
        }
        catch (const out_of_range& e) { //ver -- diviidri em data ?? ou problema dizer maneira genenrica
            handleErrors("This UC doesn't exist in the database.");
            handleErrors("This class doesn't exist in the database for the given UC.");
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}

void App::consultStudentsCourse() {
    bool shouldExit = false;

    while(!shouldExit) {
        try {
            string courseCode = UserInterface::readCode("Insert the UC code (i.e.: L.EIC001): ");
            string msg = data.consultStudentsCourse(courseCode);
            UserInterface::printMessage(msg);
            UserInterface::pressEnterToContinue();
            break;
        }
        catch (const out_of_range& e) {
            handleErrors("This UC doesn't exist in the database.");
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}


void App::consultStudentsYear() { //errors
    bool shouldExit = false;

    while(!shouldExit) {
        try {
            int year = stoi(UserInterface::readCode("Year: "));
            string msg = data.consultStudentsYear(year); //consult n da bem
            UserInterface::printMessage(msg);
            UserInterface::pressEnterToContinue();
            break;
        }
        catch (const invalid_argument& e) {  //situacao stoi
            handleErrors("Invalid year.");
            shouldExit = tryAgainMenu();
        }
        catch (const out_of_range& e) {
            handleErrors("This year doesn't exist in the database.");
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();

}



void App::consultNumStudentsUcs() { //usei stoi
    bool shouldExit = false;

    while (!shouldExit) {
        try {
            int nUcs = stoi(UserInterface::readCode("How many Ucs: "));
            if (nUcs > 7) throw out_of_range("Invalid number. The student cant be in more than 7 Ucs.");
            string msg = data.consultNumStudentsUcs(nUcs);
            UserInterface::printMessage(msg);
            UserInterface::pressEnterToContinue();
            break;
        }
        catch (const invalid_argument &e) {
            handleErrors("Invalid number.");
            shouldExit = tryAgainMenu();
        }
        catch (const out_of_range &e) {
            handleErrors(e.what());
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}

void App::consultClassYearUcOccupation() {   //separo?

}

void App::consultBiggestUc() { //falta ordenar

    string msg = data.consultBiggestUc();
    UserInterface::printMessage(msg);
    UserInterface::pressEnterToContinue();

    UserInterface::printConsultMenu();
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

void App::newRequestAdd() { //errros
    bool shouldExit = false;

    while(!shouldExit) {
        try {
            int studentCode = stoi(UserInterface::readCode("Student Code (i.e.: 123456789): ")); //invalid arg
            string ucCode = UserInterface::readCode("Insert the UC code (i.e.: L.EIC001): ");
            string classCode = UserInterface::readCode("Insert the Class Code (i.e.: 1LEIC01): ");
            data.createAddRequest(studentCode,ucCode,classCode);
            UserInterface::pressEnterToContinue();
            break;
        }
        catch (const invalid_argument& e) {
            handleErrors("Invalid student code. Please ensure the student code consists of numeric digits only.");
            shouldExit = tryAgainMenu();
        }
        catch(const invalid_argument& e){ //??
            handleErrors("This UC doesn't exist in the database.");
            handleErrors("This class doesn't exist in the database for the given UC.");
            shouldExit = tryAgainMenu();
        }
        catch (const out_of_range& e) {
            handleErrors("This student doesn't exist in the database.");
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}

void App::newRequestRemove() { //errors
    bool shouldExit = false;

    while(!shouldExit) {
        try {
            int studentCode = stoi(UserInterface::readCode("Student Code (i.e.: 123456789): "));
            string ucCode = UserInterface::readCode("Insert the UC code (i.e.: L.EIC001): ");
            data.createRemoveRequest(studentCode,ucCode);
            UserInterface::pressEnterToContinue();
            break;
        }
        catch (const invalid_argument& e) {
            handleErrors("Invalid student code. Please ensure the student code consists of numeric digits only.");
            shouldExit = tryAgainMenu();
        }
        catch(const invalid_argument& e){ //??
            handleErrors("This UC doesn't exist in the database.");
            handleErrors("This class doesn't exist in the database for the given UC.");
            shouldExit = tryAgainMenu();
        }
        catch (const out_of_range& e) {
            handleErrors("This student doesn't exist in the database.");
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}

void App::newRequestSwitch() { //errors
    bool shouldExit = false;

    while(!shouldExit) {
        try {
            int studentCode = stoi(UserInterface::readCode("Student Code (i.e.: 123456789): "));
            string ucCode = UserInterface::readCode("Insert the UC code (i.e.: L.EIC001): ");
            string classCodeOrigin = UserInterface::readCode("Insert the Class Code Origin (i.e.: 1LEIC01): "); //??
            string classCodeDestiny = UserInterface::readCode("Insert the Class Code Destiny (i.e.: 1LEIC01): ");
            data.createSwitchRequest(studentCode,ucCode,classCodeOrigin,classCodeDestiny);
            //recebr algum tipo de msg a dizer sobre a mudanca??
            UserInterface::pressEnterToContinue();
            break;
        }
        catch (const invalid_argument& e) {
            handleErrors("Invalid student code. Please ensure the student code consists of numeric digits only.");
            shouldExit = tryAgainMenu();
        }
        catch(const invalid_argument& e){ //??
            handleErrors("This UC doesn't exist in the database.");
            handleErrors("This class doesn't exist in the database for the given UC.");
            shouldExit = tryAgainMenu();
        }
        catch (const out_of_range& e) {
            handleErrors("This student doesn't exist in the database.");
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
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


