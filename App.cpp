#include "App.h"

#include <ios>
#include <iostream>

App::App() {}

void App::run() {
    try {
        this->data.loadData();
        mainMenu();
    } catch (const ios_base::failure& e) {
        handleErrors(e.what());
    } catch (const out_of_range& e) {
        handleErrors("Error reading the saves files. Invalid Data");
    }
}

void App::close() { this->data.saveData(); }

void App::handleErrors(const string& error) {
    UserInterface::printError(error);
}

void App::mainMenu() {
    UserInterface::printMainMenu();
    bool shouldExit = false;
    bool inputError;
    do {
        inputError = false;
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
                inputError = true;
                break;
        }
    } while (inputError || !shouldExit);
}

void App::consultMenu() {
    UserInterface::printConsultMenu();
    bool shouldExit = false;
    bool inputError;
    do {
        inputError = false;

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
                consultBiggestUc();
                break;
            case 'q':
                shouldExit = true;
                break;
            default:
                handleErrors("Invalid Input");
                inputError = true;
                break;
        }
    } while (inputError || !shouldExit);

    UserInterface::printMainMenu();
}

bool App::tryAgainMenu() {
    bool shouldExit = false;
    bool inputError;
    do {
        inputError = false;
        UserInterface::printTryAgainMenu();
        switch (UserInterface::readOption("Select an option: ")) {
            case '1':
                break;
            case 'q':
                shouldExit = true;
                break;
            default:
                handleErrors("Invalid Input");
                inputError = true;
                break;
        }
    } while (inputError);

    return shouldExit;
}

void App::consultStudentSchedule() {
    bool shouldExit = false;

    while (!shouldExit) {
        try {
            int studentCode = stoi(
                UserInterface::readCode("Student Code (i.e.: 123456789): "));
            Student student = data.getStudent(studentCode);
            UserInterface::printStudentSchedule(student);
            UserInterface::pressEnterToContinue();
            break;
        } catch (const out_of_range& e) {
            handleErrors("This student doesn't exist in the database.");
            shouldExit = tryAgainMenu();
        } catch (const invalid_argument& e) {
            handleErrors(
                "Invalid student code. Please ensure the student code consists "
                "of numeric digits only.");
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}

void App::consultClassSchedule() {  // fazer aassimm ou mensagem com textos
    bool shouldExit = false;

    while (!shouldExit) {
        try {
            string classCode = UserInterface::readCode(
                "Insert the Class Code (i.e.: 1LEIC01): ");
            set<string> ucs = data.getUcsByClassCode(classCode);

            unordered_map<string, int> weekdayToWeekdayNumberMap = {
                {"Monday", 0},
                {"Tuesday", 1},
                {"Wednesday", 2},
                {"Thursday", 3},
                {"Friday", 4}};

            map<int, set<string>> schedulesByDay;
            for (const string& ucCode : ucs) {
                Class c = data.getAllUcs().at(ucCode).getClass(classCode);
                for (const ClassSchedule& classSchedule :
                     c.getAllClassSchedules()) {
                    string ss = classSchedule.getTimeInterval()
                                    .getTimeIntervalAsString() +
                                " " + c.getUcCode() + " (" +
                                classSchedule.getType() + ")";

                    schedulesByDay[weekdayToWeekdayNumberMap.at(
                                       classSchedule.getWeekday())]
                        .insert(ss);
                }
            }
            UserInterface::printClassSchedule(classCode, ucs, schedulesByDay);
            UserInterface::pressEnterToContinue();
            break;
        } catch (const out_of_range& e) {
            handleErrors("This class doesn't exist in the database.");
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}

void App::consultStudentsClass() {  // ordenar
    bool shouldExit = false;

    while (!shouldExit) {
        try {
            string ucCode = UserInterface::readCode(
                "Insert the UC code (i.e.: L.EIC001): ");
            string classCode = UserInterface::readCode(
                "Insert the Class Code (i.e.: 1LEIC01): ");
            string msg = data.consultStudentsClass(ucCode, classCode);
            UserInterface::printMessage(msg);
            UserInterface::pressEnterToContinue();
            break;
        } catch (const invalid_argument& e) {
            handleErrors(e.what());

            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}

void App::consultStudentsCourse() {  // ordenar
    bool shouldExit = false;

    while (!shouldExit) {
        try {
            string ucCode = UserInterface::readCode(
                "Insert the UC code (i.e.: L.EIC001): ");
            string msg = data.consultStudentsCourse(ucCode);
            UserInterface::printMessage(msg);
            UserInterface::pressEnterToContinue();
            break;
        } catch (const invalid_argument& e) {
            handleErrors(e.what());

            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}

void App::consultStudentsYear() {  // errors stoi
    bool shouldExit = false;

    while (!shouldExit) {
        try {
            string year = UserInterface::readCode("Year: ");
            string msg = data.consultStudentsYear(year);
            UserInterface::printMessage(msg);
            UserInterface::pressEnterToContinue();
            break;
        } catch (const invalid_argument& e) {
            handleErrors(e.what());
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}

void App::consultNumStudentsUcs() {
    bool shouldExit = false;

    while (!shouldExit) {
        try {
            string nUcs = UserInterface::readCode("How many Ucs: ");
            string msg = data.consultNumStudentsUcs(nUcs);
            UserInterface::printMessage(msg);
            UserInterface::pressEnterToContinue();
            break;
        } catch (const invalid_argument& e) {
            handleErrors(e.what());
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}

void App::consultBiggestUc() {  // falta ordenar

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
        inputError = false;
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
                shouldExit = true;
                break;
            default:
                handleErrors("Invalid Input");
                inputError = true;
                break;
        }
    } while (inputError || !shouldExit);

    UserInterface::printMainMenu();
}

void App::newRequestAdd() {
    bool shouldExit = false;

    while (!shouldExit) {
        try {
            string studentCode =
                UserInterface::readCode("Student Code (i.e.: 123456789): ");
            string ucCode = UserInterface::readCode(
                "Insert the UC code (i.e.: L.EIC001): ");
            string classCode = UserInterface::readCode(
                "Insert the Class Code (i.e.: 1LEIC01): ");
            data.createAddRequest(studentCode, ucCode, classCode);
            UserInterface::printMessage(
                "Your request was saved in the pending request list.");
            UserInterface::pressEnterToContinue();
            break;
        } catch (const invalid_argument& e) {
            handleErrors(e.what());
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printNewRequestMenu();
}

void App::newRequestRemove() {
    bool shouldExit = false;

    while (!shouldExit) {
        try {
            string studentCode =
                UserInterface::readCode("Student Code (i.e.: 123456789): ");
            string ucCode = UserInterface::readCode(
                "Insert the UC code (i.e.: L.EIC001): ");
            data.createRemoveRequest(studentCode, ucCode);
            UserInterface::printMessage(
                "Your request was saved in the pending request list.");
            UserInterface::pressEnterToContinue();
            break;
        } catch (const invalid_argument& e) {
            handleErrors(e.what());
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printNewRequestMenu();
}

void App::newRequestSwitch() {
    bool shouldExit = false;

    while (!shouldExit) {
        try {
            string studentCode =
                UserInterface::readCode("Student Code (i.e.: 123456789): ");
            string ucCode = UserInterface::readCode(
                "Insert the UC code (i.e.: L.EIC001): ");
            string classCodeDestiny = UserInterface::readCode(
                "Insert the Class Code Destiny (i.e.: 1LEIC01): ");
            data.createSwitchRequest(studentCode, ucCode, classCodeDestiny);
            UserInterface::printMessage(
                "Your request was saved in the pending request list.");
            UserInterface::pressEnterToContinue();
            break;
        } catch (const invalid_argument& e) {
            handleErrors(e.what());
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printNewRequestMenu();
}

void App::processRequestMenu() {
    UserInterface::printProcessRequestMenu();
    bool shouldExit;
    bool inputError;
    do {
        inputError = false;
        switch (UserInterface::readOption("Select an option: ")) {
            case '1':
                processPendingRequests();
                break;
            case '2':
                recentActions();
                break;
            case '3':
                undoRecentActions();
                break;
            case 'q':
                shouldExit = true;
                break;
            default:
                handleErrors("Invalid Input");
                inputError = true;
                break;
        }
    } while (inputError || !shouldExit);
}

void App::processPendingRequests() {  //??

    const string& message = data.processRequests();
    UserInterface::printMessage(message);
    UserInterface::pressEnterToContinue();
    UserInterface::printProcessRequestMenu();
}

void App::recentActions() {  //??
    /*
    data.getRequestHistory();
    UserInterface::pressEnterToContinue();
    UserInterface::printProcessRequestMenu();
     */
}

void App::undoRecentActions() {  //??
    // falta implementat ligar edu
}
