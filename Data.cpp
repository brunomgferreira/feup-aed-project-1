#include "Data.h"

#include <fstream>
#include <stdexcept>

#include "Request.h"
#include "Student.h"

using namespace std;

/**
 * @brief Standard constructor of the class Data.
 * @details Time complexity: O(1)
 */

Data::Data() {}

/**
 * @brief Returns all the UCs.
 * @details Time complexity: O(1)
 * @return ucs of data
 */

map<string, Uc> Data::getAllUcs() const { return this->ucs; }

/**
 * @brief Returns a UC given a UC code.
 * @details Time complexity: O(log(n))
 * @param ucCode UC code of the UC to be returned
 * @return UC with code == ucCode
 */

Uc &Data::getUc(const string &ucCode) { return this->ucs.at(ucCode); }

/**
 * @brief checks if a class exists
 * @details Time complexity: O(nlog(n))
 * @param classCode Code of the class to check if exists
 * @return true if a class with classCode exists, otherwise false
 */

bool Data::classExists(const string &classCode) {
    for (const auto &[ucCode, uc] : this->ucs) {  // n
        auto allClasses = uc.getAllClasses();
        if (allClasses.find(classCode) != allClasses.end()) {  // log(n)
            return true;
        }
    }
    return false;
}

/**
 * @brief Returns all the students.
 * @details Time complexity: O(1)
 * @return students of data
 */

map<int, Student> Data::getAllStudents() const { return this->students; }

/**
 * @brief Returns a student given a student code.
 * @details Time complexity: O(log(n))
 * @param studentCode student code of the student to be returned
 * @return student with code == studentCode
 */

Student &Data::getStudent(int studentCode) {
    return this->students.at(studentCode);
}

/**
 * @brief Checks if a student exists
 * @details Time complexity: O(log(n))
 * @param studentCode code of the student to check if exists
 * @return true if student exists, otherwise false
 */

bool Data::studentExists(int studentCode) {
    return (this->students.find(studentCode) != this->students.end());
}

/*
 *@brief Adds a new request of type Add to the pendent requests list
 *@details Time complexity: O(1)
 *@param studentCode The first parameter: Code of the student whose schedule
 *changes
 *@param destinyClassCode The second parameter: The code of the class the
 *student wants to join
 */

void Data::createAddRequest(int studentCode, const string &ucCode,
                            const string &destinyclassCode) {
    Request newRequest(studentCode, 'A', ucCode, "", destinyclassCode);
    this->pendentRequests.push(newRequest);
}
/*
 *@brief Adds a new request of type Switch to the pendent requests list
 *@details Time complexity: O(1)
 *@param studentCode The first parameter: Code of the student whose schedule
 *changes
 *@param originClassCode The second parameter: The code of the class the student
 *wants to leave
 *@param destinyClassCode The third parameter: The code of the class the student
 *wants to join
 */

void Data::createSwitchRequest(int studentCode, const string &ucCode,
                               const string &originClassCode,
                               const string &destinyClassCode) {
    Request newRequest(studentCode, 'S', ucCode, originClassCode,
                       destinyClassCode);
    this->pendentRequests.push(newRequest);
}

/*
 *@brief Adds a new request of type Add to the pendent requests list
 *@details Time complexity: O(1)
 *@param studentCode The first parameter: Code of the student whose schedule
 *changes
 *@param originClassCode The second parameter: The code of the class the student
 *wants to leave
 */

void Data::createRemoveRequest(int studentCode, const string &ucCode) {
    string originClassCode = students.at(studentCode).getUcClassCode(ucCode);
    Request newRequest(studentCode, 'R', ucCode, originClassCode, "");
    this->pendentRequests.push(newRequest);
}

void Data::processRequests() {
    while (!this->pendentRequests.empty()) {
        Request &request = this->pendentRequests.front();
        if (validRequest(request)) {
            applyRequest(request);
        }
        this->pendentRequests.pop();
    }
}

bool Data::validRequest(const Request &request) const {
    const Student &student = students.at(request.studentCode);
    const Uc &uc = ucs.at(request.ucCode);

    if (!uc.balancedClasses(request.originClassCode,
                            request.destinyClassCode)) {
        return false;
    }
    if (request.type != 'R') {
        Class &destinyClass = uc.getClass(request.destinyClassCode);
        if ((student.numberOfUcs() >= 7 && request.type == 'A') ||
            !destinyClass.hasVacancies() || !student.hasUc(request.ucCode)) {
            return false;
        };
        return student.verifyClass(request.originClassCode,
                                   request.destinyClassCode);
    }
    return true;
}

// Não pode ser referencia porque depois ele é apagado???
void Data::applyRequest(Request request) {
    requestHistory.push_front(request);
    Student &student = students.at(request.studentCode);
    if (request.type != 'A') {
        student.removeClass(request.originClassCode);
    }
    if (request.type != 'R') {
        const Class &newClass =
            ucs.at(request.ucCode).getClass(request.destinyClassCode);
        student.addClass(newClass);
    }
}

void Data::readRequestHistoryFile(ifstream &file) {
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string originClassCode, destinyClassCode, ucCode;
        int studentCode;
        char type;
        ss >> studentCode >> type >> originClassCode >> destinyClassCode >>
            ucCode;
        Request request(studentCode, type, ucCode, originClassCode,
                        destinyClassCode);
        requestHistory.push_front(request);
    }
}

void Data::writeClassesFile(ofstream &file) {
    while (!requestHistory.empty()) {
        const Request &request = requestHistory.front();
        file << request.studentCode << " ";
        file << request.type << " ";
        file << request.ucCode << " ";
        file << request.originClassCode << " ";
        file << request.destinyClassCode << "\n";
        requestHistory.pop_front();
    }
}

/**
 * @brief Reads the classes_per_uc.csv file. ucs is set to the read values.
 * @details Time complexity: O(n ( log(m) + log(k) ) where n is the number of
 * lines in the file, m is the number of UCs, and k is the number of classes of
 * a given UC
 * @param file classes_per_uc.csv file as ifstream
 */

void Data::readClassesPerUcFile(ifstream &file) {
    string line;
    getline(file, line);

    while (getline(file, line))  // n
    {
        replace(line.begin(), line.end(), ',', ' ');

        stringstream ss(line);

        string ucCode, classCode;

        ss >> ucCode >> classCode;
        auto it = this->ucs.find(ucCode);  // log(m)

        if (it == this->ucs.end()) {
            Uc newUc(ucCode);
            Class newClass(ucCode, classCode);

            newUc.addClass(newClass);
            ucs[ucCode] = {newUc};  // log(m)
        } else {
            Class newClass(ucCode, classCode);
            this->ucs.at(ucCode).addClass(newClass);  // log(m) + log(k)
        }
    }
}

/**
 * @brief Updates the classes_per_uc.csv file.
 * @details Time complexity: O(n * m) where n is the number of UCs,
 * and m is the number of classes of a given UC
 * @param file classes_per_uc.csv file as ofstream
 */

void Data::writeClassesPerUcFile(ofstream &file) {
    file << "UcCode,ClassCode"
         << "\n";

    for (const auto &[ucCode, Uc] : this->ucs)  // n
    {
        for (const auto &[classCode, c] : Uc.getAllClasses())  // m
        {
            file << ucCode << "," << classCode << "\n";
        }
    }
}

/**
 * @brief Reads the classes.csv file. the classSchedules inside their
 * corresponding class and uc are set to the read values.
 * @details Time complexity: O(n ( 2m + log(k) + log(v) ) where n is the number
 * of lines in the file, m is the length of the line, k is the number of UCs,
 * and v is the number of classes of a given UC
 * @param file classes.csv file as ifstream
 */

void Data::readClassesFile(ifstream &file) {
    string line;
    getline(file, line);

    while (getline(file, line))  // n
    {
        replace(line.begin(), line.end(), ',', ' ');  // m

        stringstream ss(line);  // m

        string classCode, ucCode;
        double startHour, duration;
        string weekday, type;

        ss >> classCode >> ucCode >> weekday >> startHour >> duration >> type;

        Class &currentClass =
            ucs.at(ucCode).getClass(classCode);  // log(k) + log(v)

        const TimeInterval time(startHour, duration);
        ClassSchedule newSchedule(weekday, time, type);

        currentClass.addClassSchedule(newSchedule);  // 1
    }
}

/**
 * @brief Updates the classes.csv file.
 * @details Time complexity: O(n * m * k) where n is the number of UCs,
 * m is the number of classes of a given UC,
 * and k is the number of classes of a given class
 * @param file classes.csv file as ofstream
 */

void Data::writeClassesFile(ofstream &file) {
    file << "ClassCode,UcCode,Weekday,StartHour,Duration,Type"
         << "\n";

    for (const auto &[ucCode, Uc] : this->ucs)  // n
    {
        for (const auto &[classCode, c] : Uc.getAllClasses())  // m
        {
            for (const auto &schedule : c.getAllClassSchedules())  // k
            {
                file << classCode << "," << ucCode << ","
                     << schedule.getWeekday() << "," << schedule.getStartHour()
                     << "," << schedule.getDuration() << ","
                     << schedule.getType() << "\n";
            }
        }
    }
}

/**
 * @brief Reads the students_classes.csv file. the students is set to the read
 * values.
 * @details Time complexity: O(n ( 3m + r + log(k) + log(v) + log(s) + 2log(u) +
 * log(p) ) where n is the number of lines in the file, m is the length of the
 * line, r is ts the length of the name, k is the number of UCs, v is the number
 * of classes of a given UC, s is the number of students in a given class, u is
 * the total number of students, and p is the number of UCs of a given student
 * @param file classes.csv file as ifstream
 */

void Data::readStudentsClassesFile(ifstream &file) {
    string line;
    getline(file, line);

    while (getline(file, line))  // n
    {
        replace(line.begin(), line.end(), ' ', '?');  // m
        replace(line.begin(), line.end(), ',', ' ');  // m

        stringstream ss(line);  // m

        int studentCode;
        string studentName, classCode, ucCode;

        ss >> studentCode >> studentName >> ucCode >> classCode;

        replace(studentName.begin(), studentName.end(), '?', ' ');  // r

        Class &currentClass =
            this->ucs.at(ucCode).getClass(classCode);  // log(k) + log(v)
        currentClass.addStudent(studentCode);          // log(s)

        auto it = students.find(studentCode);  // log(u)
        if (it == students.end()) {
            Student newStudent(studentCode, studentName);
            newStudent.addClass(currentClass);  // log(p)

            this->students[studentCode] = {newStudent};  // log(u)
        } else {
            it->second.addClass(currentClass);  // log(p)
        }
    }
}

/**
 * @brief Updates the students_classes.csv file.
 * @details Time complexity: O(n * m) where n is the number of students,
 * and m is the number of UCs of a given student
 * @param file students_classes.csv file as ofstream
 */

void Data::writeStudentsClassesFile(ofstream &file) {
    file << "StudentCode,StudentName,UcCode,ClassCode"
         << "\n";

    for (const auto &[studentCode, student] : this->students)  // n
    {
        for (const auto &[ucCode, c] : student.getAllClasses())  // m
        {
            file << studentCode << "," << student.getStudentName() << ","
                 << ucCode << "," << c.getClassCode() << "\n";
        }
    }
}
