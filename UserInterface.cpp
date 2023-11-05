#include <limits>
#include <unordered_map>
#include "UserInterface.h"
#include <iomanip>


void UserInterface::printError(const string& error) {
    cout << "ERROR: "<< error << endl;
}

void UserInterface::printMessage(const string& msg) {
    cout << msg << endl;
}

char UserInterface::readOption(const string& msg) {
    char input;
    cout << endl << msg;
    cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

string UserInterface::readCode(const string& msg) {
    string input;
    cout << endl << msg;
    cin >> input;
    return input;
}

int UserInterface::readNumber(const string& msg) { //sem uso usei readcode
    int input;
    cout << endl << msg;
    cin >> input;
    return input;
}

void UserInterface::printMainMenu() {
    cout << endl;
    cout << "======= Main Menu =======" << endl;
    cout << "\n"
            "1 - Consult\n"
            "2 - New Request\n"
            "3 - Process Request\n\n"
            "q - Exit\n"
            "=========================";
}


void UserInterface::printConsultMenu() {
    cout << endl;
    cout << "===== Consult Menu =====" << endl;
    cout << "\n"
            "Schedule:\n"
            "1 - Of a given student\n"
            "2 - Of a given class\n"
            "Students:\n"
            "3 - Within a given class\n" //ordencaoa
            "4 - Within a given course\n" //ordencaoa
            "5 - Within a given year\n" //ordencaoa
            "Occupation:\n"
            "6 - Within a given class\n"
            "7 - Within a given course\n"
            "8 - Within a given year\n"
            "Extra:\n"
            "9 - The number of students registered in at least n UCs\n"
            "0 - The UCs with the greatest number of students\n\n" //mudar texto? aparece tudo ordencado

            "q - Back to Main Menu\n"
            "==============================";
}

void UserInterface::printStudentSchedule(const Student& student) {
    unordered_map<string, int> weekdayToWeekdayNumberMap = {
            {"Monday", 0},
            {"Tuesday", 1},
            {"Wednesday", 2},
            {"Thursday", 3},
            {"Friday", 4}
    };
    unordered_map<int, string> weekdayNumberToWeekdayMap = {
            {0, "Monday"},
            {1, "Tuesday"},
            {2, "Wednesday"},
            {3, "Thursday"},
            {4, "Friday"},
    };

    map<int,set<string>> schedulesByDay;

    cout << endl << string(170, '#') << endl;
    cout << "Student Code:\t" << student.getStudentCode() << endl;
    cout << "Student Name:\t" << student.getStudentName() << endl;
    cout << "Enrolled in " << student.getAllClasses().size() << " UCs:\t";

    for(auto [ucCode, c] : student.getAllClasses()) {
        cout << "[" << ucCode << "-" << c.getClassCode() << "]\t";
        for(const ClassSchedule &classSchedule : c.getAllClassSchedules()) {
            string ss =  classSchedule.getTimeInterval().getTimeIntervalAsString() + " "
                            + ucCode + "-" + c.getClassCode() + " (" + classSchedule.getType() + ")";

            schedulesByDay[weekdayToWeekdayNumberMap.at(classSchedule.getWeekday())].insert(ss);
        }
    }

    cout << endl << string(170, '#') << endl;
    cout << endl;
    for (auto [weekdayNumber, schedules] : schedulesByDay) {
        cout << left << setw(10) << weekdayNumberToWeekdayMap.at(weekdayNumber) << ":\t";

        for (const string& schedule : schedules) {
            cout << left << setw(35) << schedule << " \t";
        }
        cout << endl;
    }
    cout << endl;
    cout << string(170, '#') << endl;
}

void UserInterface::printClassSchedule(const string& classCode, const set<string>& ucs, const map<int,set<string>>& schedulesByDay) {
    unordered_map<int, string> weekdayNumberToWeekdayMap = {
            {0, "Monday"},
            {1, "Tuesday"},
            {2, "Wednesday"},
            {3, "Thursday"},
            {4, "Friday"},
    };

    cout << endl << string(120, '#') << endl;
    cout << "Class Code: " << classCode << endl;
    cout << "UCs: ";
    for(const string ucCode : ucs) {
        cout << ucCode << "\t";
    }

    cout << endl << string(120, '#') << endl;
    cout << endl;
    for (auto [weekdayNumber, schedules] : schedulesByDay) {
        cout << left << setw(10) << weekdayNumberToWeekdayMap.at(weekdayNumber) << ":\t";

        for (const auto& schedule : schedules) {
            cout << left << setw(30) << schedule << " \t";
        }
        cout << endl;
    }
    cout << endl;
    cout << string(120, '#') << endl;
}

void UserInterface::printTryAgainMenu() {
    cout << "\n"
            "---------------\n"
            "1 - Try again\n"
            "q - Go back\n"
            "---------------\n";
}

void UserInterface::pressEnterToContinue() {
    cout << "Press ENTER to continue... ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

void UserInterface::printNewRequestMenu() {
    cout << endl;
    cout << "====== New Request Menu =====" << endl;
    cout << "\n"
            "1 - Add Request\n" //Nome request do tipo add nao add request??
            "2 - Remove Request\n"
            "3 - Switch Request\n\n"
            "q - Back to Main Menu\n"
            "=============================";
}

void UserInterface::printProcessRequestMenu() {
    cout << endl;
    cout << "===== Process Request Menu ====" << endl;
    cout << "\n"
            "1 - Process Pending Requests\n"
            "2 - See recent actions \n"
            "3 - Undo recent actions \n\n"
            "q - Back to Main Menu\n"
            "===============================";
}









