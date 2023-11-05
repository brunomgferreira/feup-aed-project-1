#include "Data.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Request.h"
#include "Student.h"

using namespace std;

bool Data::isNumeric(const string &str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

Data::Data() {}

map<string, Uc> Data::getAllUcs() const { return this->ucs; }

Uc &Data::getUc(const string &ucCode) { return this->ucs.at(ucCode); }


bool Data::ucExists(const std::string &ucCode) {
    for (const auto &[code, uc] : this->ucs) {
        if (code == ucCode) return true;
    }
    return false;
}

string Data::consultStudentsClass(const string &ucCode,
                                  const string &classCode) {
    if (!ucExists(ucCode))
        throw invalid_argument("This UC doesn't exist in the database.");
    Uc uc = this->ucs.at(ucCode);
    if (!classExists(ucCode, classCode))
        throw invalid_argument("This Class doesn't exist in the database.");
    Class c = uc.getClass(classCode);
    set<int> studentCodes = c.getAllStudents();
    stringstream res;
    res << string(170, '#') << endl << endl;
    for (const int studentCode : studentCodes) {
        Student student = this->students.at(studentCode);
        res << student.getStudentAsString() << endl;
    }
    res << endl << string(170, '#') << endl << endl;
    return res.str();
}


string Data::consultStudentsCourse(const string &ucCode) {
    if (!ucExists(ucCode))
        throw invalid_argument("This UC doesn't exist in the database.");
    Uc uc = this->ucs.at(ucCode);
    stringstream res;
    res << string(170, '#') << endl << endl;
    for (auto [ucCode, c] : uc.getAllClasses()) {
        res << "Class: " << c.getClassCode() << endl;
        for (auto studentCode : c.getAllStudents()) {
            Student student = getStudent(studentCode);
            res << student.getStudentAsString() << endl;
        }
        res << endl;
    }
    res << string(170, '#') << endl << endl;
    return res.str();
}


string Data::consultStudentsYear(const string &year) {
    if (!isNumeric(year))
        throw invalid_argument("The year should be a number.");
    int intYear = stoi(year);
    if (intYear > 3)
        throw invalid_argument(
            "This year doesn't exist in the context of the database.");
    stringstream res;
    set<int> std;
    res << string(170, '#') << endl << endl;
    for (auto [uccode, uc] : this->ucs) {
        for (auto [ucCode, c] : uc.getAllClasses()) {
            if (c.getClassCode().substr(0, 1) == to_string(intYear)) {
                for (const int &studentCode : c.getAllStudents()) {
                    std.insert(studentCode);
                }
            } else
                break;
        }
    }
    for (auto studentCode : std) {
        Student student = getStudent(studentCode);
        res << student.getStudentAsString() << endl;
    }
    res << endl;
    res << string(170, '#') << endl << endl;
    return res.str();
}


string Data::consultOccupationClass(const string &ucCode,
                                    const string &classCode) {
    if (!ucExists(ucCode))
        throw invalid_argument("This UC doesn't exist in the database.");
    Uc uc = this->ucs.at(ucCode);
    if (!classExists(ucCode, classCode))
        throw invalid_argument("This Class doesn't exist in the database.");
    Class c = uc.getAllClasses().at(classCode);
    stringstream res;
    res << endl << "Uc: " << ucCode << "   Class: " << classCode << endl;
    res << "Number of students: " << c.numberStudents() << endl;
    res << "Number of vacancies: " << c.numberVacancies() << endl << endl;
    return res.str();
}


string Data::consultOccupationCourse(const string &ucCode) {
    if (!ucExists(ucCode))
        throw invalid_argument("This UC doesn't exist in the database.");
    Uc uc = this->ucs.at(ucCode);
    stringstream res;
    int numberStudents = 0;
    int numberVacancies = 0;
    for (auto [ucCode, c] : uc.getAllClasses()) {
        numberStudents += c.numberStudents();
        numberVacancies += c.numberVacancies();
    }
    res << endl << "Uc: " << ucCode << endl;
    res << "Number of students: " << numberStudents << endl;
    res << "Number of vacancies: " << numberVacancies << endl << endl;
    return res.str();
}


string Data::consultOccupationYear(const string &year) {
    if (!isNumeric(year))
        throw invalid_argument("The year should be a number.");
    int intYear = stoi(year);
    if (intYear > 3)
        throw invalid_argument(
            "This year doesn't exist in the context of the database.");
    stringstream res;
    set<int> std;
    for (auto [uccode, uc] : this->ucs) {
        for (auto [ucCode, c] : uc.getAllClasses()) {
            if (c.getClassCode().substr(0, 1) == to_string(intYear)) {
                for (const int &studentCode : c.getAllStudents()) {
                    std.insert(studentCode);
                }
            } else
                break;
        }
    }
    res << endl << "Year: " << year << endl;
    res << "Number of students: " << std.size() << endl << endl;
    return res.str();
}


string Data::consultNumStudentsUcs(const string &nUcs) {
    if (!isNumeric(nUcs))
        throw invalid_argument("The year should be a number.");
    int intNUcs = stoi(nUcs);
    if (intNUcs > 7)
        throw invalid_argument(
            "Invalid number. The student cant be in more than 7 Ucs.");
    int n = 0;
    stringstream res;
    for (auto [studentCode, student] : this->students) {
        if (student.numberOfUcs() >= intNUcs) n++;
    }
    res << endl
        << "There is " << n << " students registered in at least " << intNUcs
        << endl
        << endl;
    return res.str();
}


string Data::consultBiggestUc(bool ascendingOrder) {
    vector<pair<string, int>> ucData;

    for (auto [ucCode, uc] : this->ucs) {
        int totalStudents = 0;
        for (auto [ucCode2, c] : uc.getAllClasses()) {
            totalStudents += c.numberStudents();
        }
        ucData.emplace_back(ucCode, totalStudents);
    }

    auto auxSort = [ascendingOrder](const pair<string, int> &pair1,
                                    const pair<string, int> &pair2) {
        return ascendingOrder ? (pair1.second < pair2.second)
                              : (pair1.second > pair2.second);
    };

    sort(ucData.begin(), ucData.end(), auxSort);

    stringstream res;
    for (const auto &ucInfo : ucData) {
        res << ucInfo.first << " -- " << ucInfo.second << " students" << endl;
    }
    return res.str();
}

set<string> Data::getUcsByClassCode(const string &classCode) const {
    return this->ucsCodesByClassCode.at(classCode);
}


bool Data::classExists(const string &ucCode, const string &classCode) {
    Uc uc = this->ucs.at(ucCode);
    return uc.hasClass(classCode);
}


Student &Data::getStudent(int studentCode) {
    return this->students.at(studentCode);
}


bool Data::studentExists(int studentCode) {
    return (this->students.find(studentCode) != this->students.end());
}


void Data::createAddRequest(const string &studentCode, const string &ucCode,
                            const string &destinyClassCode) {
    if (!isNumeric(studentCode))
        throw invalid_argument("The Student Code should be numeric.");
    int intStudentCode = stoi(studentCode);
    if (!studentExists(intStudentCode))
        throw invalid_argument("The student doesn't exist in the database.");
    if (!ucExists(ucCode))
        throw invalid_argument("This UC doesn't exist in the database.");
    if (this->students.at(intStudentCode).hasUc(ucCode))
        throw invalid_argument(
            "Student is already enrolled in that Unit Course");
    if (!classExists(ucCode, destinyClassCode))
        throw invalid_argument("This Class doesn't exist in the database.");
    Request newRequest(intStudentCode, 'A', ucCode, "", destinyClassCode);
    this->pendentRequests.push(newRequest);
}


void Data::createRemoveRequest(const string &studentCode,
                               const string &ucCode) {
    if (!isNumeric(studentCode))
        throw invalid_argument("The Student Code should be numeric.");
    int intStudentCode = stoi(studentCode);
    if (!studentExists(intStudentCode))
        throw invalid_argument("The student doesn't exist in the database.");
    if (!ucExists(ucCode))
        throw invalid_argument("This UC doesn't exist in the database.");
    if (!this->students.at(intStudentCode).hasUc(ucCode))
        throw invalid_argument("Student is not enrolled in that Unit Course");
    string originClassCode = students.at(intStudentCode).getUcClassCode(ucCode);
    Request newRequest(intStudentCode, 'R', ucCode, originClassCode, "");
    this->pendentRequests.push(newRequest);
}


void Data::createSwitchRequest(const string &studentCode, const string &ucCode,
                               const string &destinyClassCode) {
    if (!isNumeric(studentCode))
        throw invalid_argument("The Student Code should be numeric.");
    int intStudentCode = stoi(studentCode);
    if (!studentExists(intStudentCode))
        throw invalid_argument("The student doesn't exist in the database.");
    if (!ucExists(ucCode))
        throw invalid_argument("This UC doesn't exist in the database.");
    if (!classExists(ucCode, destinyClassCode))
        throw invalid_argument("This Class doesn't exist in the database.");
    string originClassCode = students.at(intStudentCode).getUcClassCode(ucCode);
    Request newRequest(intStudentCode, 'S', ucCode, originClassCode,
                       destinyClassCode);
    this->pendentRequests.push(newRequest);
}

string Data::processIndividualRequest(){
    if (pendentRequests.empty()){
        return "No requests to process.\n";
    }
    Request& request = this->pendentRequests.front();
    string validationResult = validRequest(request);

    stringstream log;
    log << "\n    Process log: \n";
    log << '\n' << "-  " << request.stringInfo();
    log << "Status: " << validationResult << '\n';

    if (validationResult == "Successful") {
        applyRequest(request, false);
    }
    this->pendentRequests.pop();
    return log.str();
}

string Data::processRequests() {
    int totalRequests = this->pendentRequests.size();
    if (totalRequests == 0) {
        return "No requests to process.\n";
    }
    stringstream log;
    log << "\n    Processes log: \n";
    int sucessfulRequests = 0;
    int requestNumber = 1;
    while (!this->pendentRequests.empty()) {
        Request &request = this->pendentRequests.front();
        string validationResult = validRequest(request);

        log << '\n' << requestNumber++ << "-  " << request.stringInfo();
        log << "Status: " << validationResult << '\n';

        if (validationResult == "Successful") {
            applyRequest(request, false);
            sucessfulRequests++;
        }
        this->pendentRequests.pop();
    }
    stringstream output;
    output << "Process finished!\n";
    output << totalRequests << " total requests processed. "
           << sucessfulRequests << " successfully accepted!\n";
    output << log.str();
    return (output.str());
}


string Data::undoRequest(const string& requestNumber) {

    if (!isNumeric(requestNumber))
        throw invalid_argument("The request number should be numeric.");
    int intRequestNumber = stoi(requestNumber);
    if (intRequestNumber > requestHistory.size() || intRequestNumber <= 0)
        throw invalid_argument("Not a valid request number.");

    stringstream output;
    output << "Processing undo request...\nStatus: ";

    auto requestIterator = requestHistory.begin();
    for (size_t i = 1; i < intRequestNumber; i++) {
        requestIterator++;
    }
    const Request &request = *requestIterator;

    int studentCode = request.studentCode;
    const string &ucCode = request.ucCode;
    const Student &student = this->students.at(studentCode);

    string destinyClassCode, originClassCode;
    char type;

    switch (request.type) {
        case 'A':
            if (!student.hasUc(ucCode)) {
                output << "Undoing request has no effect. \nInfo: Student is "
                          "already not enrolled in that UC.";
                return output.str();
            }
            type = 'R';
            originClassCode = student.getUcClassCode(ucCode);
            break;
        case 'R':
            if (student.hasUc(ucCode)) {
                output << "Undoing request has no effect. \nInfo: Student is "
                          "already enrolled in that Uc.";
                return output.str();
            }
            type = 'A';
            destinyClassCode = request.originClassCode;
            break;
        case 'S':
            if (!student.hasUc(ucCode)) {
                output << "Impossible to undo request. \nInfo: Student is no "
                          "longer enrolled in that Uc.";
                return output.str();
            }
            type = 'S';
            destinyClassCode = request.originClassCode;
            originClassCode = request.destinyClassCode;
            break;
    }
    Request oppositeRequest(studentCode, type, ucCode, originClassCode,
                            destinyClassCode);

    requestHistory.erase(requestIterator);

    string validationResult = validRequest(oppositeRequest);
    output << validationResult;
    if (validationResult == "Successful") {
        applyRequest(oppositeRequest, true);
    }
    return output.str();
}


string Data::validRequest(const Request &request) const {
    string log = "Not accepted.\nInfo: ";
    const Student &student = students.at(request.studentCode);
    Uc uc = ucs.at(request.ucCode);

    if (request.type != 'R') {
        if (!uc.balancedClasses(request.originClassCode,
                                request.destinyClassCode)) {
            log += "Operation affects Class balance.";
            return log;
        }

        Class &destinyClass = uc.getClass(request.destinyClassCode);
        if (!destinyClass.hasVacancies()) {
            log += "Class to enter does not have vacancies";
            return log;
        }
        if (student.numberOfUcs() >= 7 && request.type == 'A') {
            log +=
                "Student is already enrolled in the maximum number of Ucs "
                "possible";
            return log;
        };
        string conflictClass = student.findConflictClass(
            request.ucCode, uc.getClass(request.destinyClassCode));
        if (!conflictClass.empty()) {
            log +=
                "Class to enter conflicts with student's current schedule. "
                "There is an overlap with the class " +
                conflictClass;
            return log;
        }
    }
    return "Successful";
}


void Data::applyRequest(const Request &request, bool undo) {
    if (!undo){
        requestHistory.push_front(request);
    }
    Student &student = students.at(request.studentCode);
    if (request.type != 'A') {
        Class &oldClass =
            ucs.at(request.ucCode).getClass(request.originClassCode);
        student.removeClass(request.ucCode);
        oldClass.removeStudent(student.getStudentCode());
    }
    if (request.type != 'R') {
        Class &newClass =
            ucs.at(request.ucCode).getClass(request.destinyClassCode);
        student.addClass(newClass);
        newClass.addStudent(student.getStudentCode());
    }
}

string Data::getRequestHistory() const {
    stringstream history;
    history << "\n=== Request History === \n";
    if (this->requestHistory.empty()) {
        return "\nRequest history is empty.\n";
    }
    int requestNumber = 1;
    for (const auto &request : this->requestHistory) {
        history << '\n' << requestNumber++ << "-  " << request.stringInfo();
    }
    return history.str();
}

void Data::loadData() {
    readClassesPerUcFile();
    readClassesFile();
    readStudentsClassesFile();
    readRequestHistoryFile();
    readPendentRequestsFile();
}

void Data::saveData() {
    writeClassesFile();
    writeClassesPerUcFile();
    writeStudentsClassesFile();
    writeRequestHistoryFile();
    writePendentRequestsFile();
}

void Data::readPendentRequestsFile() {
    ifstream file(DIRECTORY_PATH + PENDENT_REQUESTS_FILENAME);
    if (file.is_open()) {
        string line;
        getline(file, line);

        while (getline(file, line)) {
            replace(line.begin(), line.end(), ',', ' ');
            stringstream ss(line);

            string originClassCode, destinyClassCode, ucCode;
            int studentCode;
            char type;
            ss >> studentCode >> type >> ucCode >> originClassCode >>
                destinyClassCode;
            originClassCode = originClassCode == "null" ? "" : originClassCode;
            destinyClassCode =
                destinyClassCode == "null" ? "" : destinyClassCode;
            Request request(studentCode, type, ucCode, originClassCode,
                            destinyClassCode);
            pendentRequests.push(request);
        }
        file.close();
    }
}

void Data::writePendentRequestsFile() {
    ofstream file(DIRECTORY_PATH + PENDENT_REQUESTS_FILENAME);
    file << "StudentCode,Type,UcCode,OriginClassCode,DestinyClassCode"
         << "\n";

    while (!pendentRequests.empty()) {
        const Request &request = pendentRequests.front();
        string originClassCode =
            request.originClassCode.empty() ? "null" : request.originClassCode;
        string destinyClassCode = request.destinyClassCode.empty()
                                      ? "null"
                                      : request.destinyClassCode;
        file << request.studentCode << ",";
        file << request.type << ",";
        file << request.ucCode << ",";
        file << originClassCode << ",";
        file << destinyClassCode << "\n";
        pendentRequests.pop();
    }
    file.close();
}

void Data::readRequestHistoryFile() {
    ifstream file(DIRECTORY_PATH + REQUESTS_HISTORY_FILENAME);
    if (file.is_open()) {
        string line;
        getline(file, line);

        while (getline(file, line)) {
            replace(line.begin(), line.end(), ',', ' ');
            stringstream ss(line);

            string originClassCode, destinyClassCode, ucCode;
            int studentCode;
            char type;
            ss >> studentCode >> type >> ucCode >> originClassCode >>
                destinyClassCode;
            originClassCode = originClassCode == "null" ? "" : originClassCode;
            destinyClassCode =
                destinyClassCode == "null" ? "" : destinyClassCode;
            Request request(studentCode, type, ucCode, originClassCode,
                            destinyClassCode);
            requestHistory.push_back(request);
        }
        file.close();
    }
}

void Data::writeRequestHistoryFile() {
    ofstream file(DIRECTORY_PATH + REQUESTS_HISTORY_FILENAME);
    file << "StudentCode,Type,UcCode,OriginClassCode,DestinyClassCode"
         << "\n";
    while (!requestHistory.empty()) {
        const Request &request = requestHistory.front();
        string originClassCode =
            request.originClassCode.empty() ? "null" : request.originClassCode;
        string destinyClassCode = request.destinyClassCode.empty()
                                      ? "null"
                                      : request.destinyClassCode;
        file << request.studentCode << ",";
        file << request.type << ",";
        file << request.ucCode << ",";
        file << originClassCode << ",";
        file << destinyClassCode << "\n";
        requestHistory.pop_front();
    }
    file.close();
}



void Data::readClassesPerUcFile() {
    ifstream file(DIRECTORY_PATH + CLASSES_PER_UC_FILENAME);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file " + CLASSES_PER_UC_FILENAME);
    }
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

        auto it2 = this->ucsCodesByClassCode.find(classCode);  // O(1)
        if (it2 == this->ucsCodesByClassCode.end()) {
            ucsCodesByClassCode[classCode] = {ucCode};  // O(1)
        } else {
            this->ucsCodesByClassCode.at(classCode).insert(ucCode);  // O(1)
        }
    }
    file.close();
}



void Data::writeClassesPerUcFile() {
    ofstream file(DIRECTORY_PATH + CLASSES_PER_UC_FILENAME);
    file << "UcCode,ClassCode"
         << "\n";

    for (const auto &[ucCode, Uc] : this->ucs)  // n
    {
        for (const auto &[classCode, c] : Uc.getAllClasses())  // m
        {
            file << ucCode << "," << classCode << "\n";
        }
    }
    file.close();
}



void Data::readClassesFile() {
    ifstream file(DIRECTORY_PATH + CLASSES_FILENAME);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file " + CLASSES_FILENAME);
    }
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
    file.close();
}


void Data::writeClassesFile() {
    ofstream file(DIRECTORY_PATH + CLASSES_FILENAME);
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
    file.close();
}



void Data::readStudentsClassesFile() {
    ifstream file(DIRECTORY_PATH + STUDENTS_CLASS_FILENAME);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file " + STUDENTS_CLASS_FILENAME);
    }
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
            getUc(ucCode).getClass(classCode);  // log(k) + log(v)
        currentClass.addStudent(studentCode);   // log(s)

        auto it = students.find(studentCode);  // log(u)
        if (it == students.end()) {
            Student newStudent(studentCode, studentName);
            newStudent.addClass(currentClass);  // log(p)

            this->students[studentCode] = {newStudent};  // log(u)
        } else {
            it->second.addClass(currentClass);  // log(p)
        }
    }
    file.close();
}


void Data::writeStudentsClassesFile() {
    ofstream file(DIRECTORY_PATH + STUDENTS_CLASS_FILENAME);
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
    file.close();
}
