#ifndef PROJETO_APP_H
#define PROJETO_APP_H

#include "Data.h"
#include "UserInterface.h"

/**
 * @brief Class that controls all the program menus and information.
 */
class App {
   private:
    Data data;

   public:
    /**
 * @brief Standard constructor of the class App.
 * @details Time complexity: O(1)
     */
    App();
    void run();
    void close();
    /**
 * @brief Method responsible for control the main menu
     */
    void mainMenu();
    /**
 * @brief Method responsible for control the try again menu
 * @return Boolean value, according to the continuity of the menu that have
     * called this method
                      */
    bool tryAgainMenu();
    /**
 * @brief Calls a method of User Interface to print the error message.
 *
 * @param error String with the error message
     */
    void handleErrors(const string& error);

    /**
 * @brief Method responsible for control the consult menu
     */
    void consultMenu();
    /**
 * @brief Method responsible for control the new request menu
     */
    void newRequestMenu();

    /**
 * @brief Method responsible for control the process request menu
     */
    void processRequestMenu();

    /**
 * @brief Method responsible for control the consult of a student schedule
     */
    void consultStudentSchedule();
    /**
 * @brief Method responsible for control the consult of a class schedule
     */
    void consultClassSchedule();
    /**
 * @brief Method responsible for control the consult of the students within a given class
     */
    void consultStudentsClass();
    /**
 * @brief Method responsible for control the consult of the students within a given course
     */
    void consultStudentsCourse();
    /**
 * @brief Method responsible for control the consult of the students within a given year
     */
    void consultStudentsYear();
    /**
 * @brief Method responsible for control the consult of the occupation within a given class
     */
    void consultOccupationClass();
    /**
 * @brief Method responsible for control the consult of the occupation within a given course
     */
    void consultOccupationCourse();

    /**
 * @brief Method responsible for control the consult of the occupation within a given year
     */
    void consultOccupationYear();
    /**
 * @brief Method responsible for control the consult of the number of students with at least n ucs
     */
    void consultNumStudentsUcs();
    /**
 * @brief Method responsible for control the consult of the number of students by uc
     */
    void consultBiggestUc();

    /**
 * @brief Method responsible for control a new add request
     */
    void newRequestAdd();

    /**
 * @brief Method responsible for control a new remove request
     */
    void newRequestRemove();
    /**
 * @brief Method responsible for control a new switch request
     */
    void newRequestSwitch();

    /**
 * @brief Method responsible for control the process of pending requests
     */
    void processPendingRequests();
    /**
     * @brief Method responsible for control the process one pending request
     */
    void processIndividualRequest();
    /**
 * @brief Method responsible for control the recent actions
     */
    void recentActions();
    /**
 * @brief Method responsible for control the process of undo earlier actions
     */
    void undoRecentActions();

};

#endif
