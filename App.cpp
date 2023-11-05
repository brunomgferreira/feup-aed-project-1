#include "App.h"

#include <ios>
#include <iostream>


/**
 * @brief Standard constructor of the class App.
 * @details Time complexity: O(1)
 */
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



/**
 * @brief Calls a method of User Interface to print the error message.
 * @details
 * @param error String with the error message
 */
void App::handleErrors(const string& error) {
    UserInterface::printError(error);
}


/**
 * @brief Method responsible for control the main menu
 */
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


/**
 * Method responsible for control the consult menu
 */
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
                consultOccupationClass();
                break;
            case '7':
                consultOccupationCourse();
                break;
            case '8':
                consultOccupationYear();
                break;
            case '9':
                consultNumStudentsUcs();
                break;
            case '0':
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


/**
 * @brief Method responsible for control the try again menu
 * @return Boolean value, according to the continuity of the menu that have called this method
 */
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


/**
 * @brief Method responsible for control the consult of a student schedule
 */
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


/**
 * @brief Method responsible for control the consult of a class schedule
 */
void App::consultClassSchedule() { //fazer aassimm ou mensagem com textos

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


/**
 * @brief Method responsible for control the consult of the students within a given class
 */
void App::consultStudentsClass() { //ordenar
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


/**
 * @brief Method responsible for control the consult of the students within a given course
 */
void App::consultStudentsCourse() { //ordenar
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


/**
 * @brief Method responsible for control the consult of the students within a given year
 */
void App::consultStudentsYear() { //ordenar
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

/**
 * @brief Method responsible for control the consult of the occupation within a given class
 */
void App::consultOccupationClass(){
    bool shouldExit = false;

    while (!shouldExit) {
        try {
            string ucCode = UserInterface::readCode("Insert the UC code (i.e.: L.EIC001): ");
            string classCode = UserInterface::readCode("Insert the Class Code (i.e.: 1LEIC01): ");
            string msg = data.consultOccupationClass(ucCode,classCode);
            UserInterface::printMessage(msg);
            UserInterface::pressEnterToContinue();
            break;
        }
        catch (const invalid_argument& e) {
            handleErrors(e.what());

            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}


/**
 * @brief Method responsible for control the consult of the occupation within a given course
 */
void App::consultOccupationCourse(){
    bool shouldExit = false;

    while (!shouldExit) {
        try {
            string ucCode = UserInterface::readCode("Insert the UC code (i.e.: L.EIC001): ");
            string msg = data.consultOccupationCourse(ucCode);
            UserInterface::printMessage(msg);
            UserInterface::pressEnterToContinue();
            break;
        }
        catch (const invalid_argument& e) {
            handleErrors(e.what());

            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}

/**
 * @brief Method responsible for control the consult of the occupation within a given year
 */
void App::consultOccupationYear(){
    bool shouldExit = false;

    while(!shouldExit) {
        try {
            string year = UserInterface::readCode("Year: ");
            string msg = data.consultOccupationYear(year);
            UserInterface::printMessage(msg);
            UserInterface::pressEnterToContinue();
            break;
        }
        catch (const invalid_argument& e) {
            handleErrors(e.what());
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printConsultMenu();
}


/**
 * @brief Method responsible for control the consult of the number of students with at least n ucs
 */
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


/**
 * @brief Method responsible for control the consult of the number of students by uc
 */
void App::consultBiggestUc() {

    bool ascendingOrder = false;
    bool shouldExit = false;
    bool inputError;
    string msg = data.consultBiggestUc(ascendingOrder);
    UserInterface::printMessage(msg);
    UserInterface::printMessage("[1] Ascending Order    [2] Descending Order    [q] Go back");
    do {
        inputError = false;
        switch (UserInterface::readOption("Select an option: ")) {
            case '1':
                ascendingOrder = false;
                break;
            case '2':
                ascendingOrder = true;
                break;
            case 'q':
                shouldExit = true;
                break;
            default:
                handleErrors("Invalid Input\n");
                UserInterface::printMessage("[1] Ascending Order    [2] Descending Order    [q] Go back");
                inputError = true;
                break;
        }
        if(!inputError) {
            msg = data.consultBiggestUc(ascendingOrder);
            UserInterface::printMessage(msg);
            UserInterface::printMessage("[1] Ascending Order    [2] Descending Order    [q] Go back");
        }
    } while (inputError || !shouldExit);
    UserInterface::printConsultMenu();
}


/**
 * @brief Method responsible for control the new request menu
 */
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


/**
 * @brief Method responsible for control a new add request
 */
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


/**
 * @brief Method responsible for control a new remove request
 */
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


/**
 * @brief Method responsible for control a new switch request
 */
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


/**
 * @brief Method responsible for control the process request menu
 */
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

    UserInterface::printMainMenu();
}


/**
 * @brief Method responsible for control the process of pending requests
 */
void App::processPendingRequests() { //??

    const string& message = data.processRequests();
    UserInterface::printMessage(message);
    UserInterface::pressEnterToContinue();
    UserInterface::printProcessRequestMenu();
}


/**
 * @brief Method responsible for control the recent actions
 */
void App::recentActions() {
    const string& message = data.getRequestHistory();
    UserInterface::printMessage(message);
    UserInterface::pressEnterToContinue();
    UserInterface::printProcessRequestMenu();
}


/**
 * @brief Method responsible for control the process of undo earlier actions
 */
void App::undoRecentActions() {  //??
    bool shouldExit = false;

    while (!shouldExit) {
        try {
            const string& message = data.undoRequest(UserInterface::readNumber("Select a request to undo: "));
            UserInterface::printMessage(message);
            UserInterface::pressEnterToContinue();
            break;
        } catch (const invalid_argument& e) {
            handleErrors(e.what());
            shouldExit = tryAgainMenu();
        }
    }
    UserInterface::printProcessRequestMenu();
}
