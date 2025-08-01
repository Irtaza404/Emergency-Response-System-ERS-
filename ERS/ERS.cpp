#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<ctime>
using namespace std;

class EmergencyReport {
private:
    int ID;
    string ReporterName, Location, Type, Status, reportedTime, PatientOutcome, reporterRole, department, description, dispatcher, responder, Priority, resolvedTime;
    bool isActive;

public:
    // Setters
    void setID(int id) { ID = id; }
    void setReporterName(const string& name) { ReporterName = name; }
    void setLocation(const string& location) { Location = location; }
    void setType(char type)
    {
        switch (type)
        {
        case '1': Type = "Fire"; break;
        case '2': Type = "Medical Emergency"; break;
        case '3': Type = "Crime"; break;
        case '4': Type = "Accident"; break;
        case '5': Type = "Other"; break;
        default: Type = "Unknown"; break;
        };
    }
    void setStatus(const string& status) { Status = status; }
    void setPatientOutcome(const string& outcome) { PatientOutcome = outcome; }
    void setReporterRole(const string& role) { reporterRole = role; }
    void setDepartment(string dept) { department = dept; }
    void setDescription(const string& desc) { description = desc; }
    void setPriority(string priority) { Priority = priority; }
    void setIsActive(bool active) { isActive = active; }
    void setDispatcher(const string& d) { dispatcher = d; }
    void setResponder(const string& r) { responder = r; }
    void setReportedTime()
    {
        time_t now = time(0);
        tm localTime;
        localtime_s(&localTime, &now);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);
        reportedTime = string(buffer);
    }
    void setResolvedTime() {
        time_t now = time(0);
        tm localTime;
        localtime_s(&localTime, &now);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);
        resolvedTime = string(buffer);
    }

    // Getters
    int getId() const { return ID; }
    string getStatus() const { return Status; }
    string getLocation() const { return Location; }
    string getType() const { return Type; }
    string getReportedTime() const { return reportedTime; }
    string getResolvedTime() const { return resolvedTime; }
    string getReporterName() const { return ReporterName; }
    string getPatientOutcome() const { return PatientOutcome; }
    string getReporterRole() const { return reporterRole; }
    string getDepartment() const { return department; }
    string getDescription() const { return description; }
    string getDispatcher() const { return dispatcher; }
    string getResponder() const { return responder; }
    string getPriority() const { return Priority; }
    bool getIsActive() const { return isActive; }

    // Display function
    void display() const {
        cout << "\n===== Emergency Report =====" << endl;
        cout << "Report ID: " << ID << endl;
        cout << "Reporter Name: " << ReporterName << endl;
        cout << "Role of Reporter: " << reporterRole << endl;
        cout << "Location: " << Location << endl;
        cout << "Department: " << department << endl;
        cout << "Type: " << Type << endl;
        cout << "Description: " << description << endl;
        cout << "Priority: " << Priority << endl;
        cout << "Reported Time: " << reportedTime << endl;
        if (!resolvedTime.empty())
            cout << "Resolved Time: " << resolvedTime << endl;
        cout << "Active: " << (isActive ? "Active" : "Closed") << "(" << Status << ")" << endl;
        if (!dispatcher.empty())
            cout << "Dispatcher : " << dispatcher << endl;
        if (!responder.empty())
            cout << "First Responder : " << responder << endl;
        if (!(PatientOutcome.empty()))
            cout << "Patient Outcome: " << PatientOutcome << endl;
        cout << "------------------------\n" << endl;
    }
    EmergencyReport()
    {
        isActive = true;
        ID = 0;
    }
};

struct User {
    string name;
    string password;
    string role;
};

// Function declarations (prototypes) only before main
int intro();
void ChiefOfficerMenu();
void supervisorMenu();
void dispatcherMenu();
void firstResponderMenu();
void citizenMenu();
void addEmergencyReport(const string&);
void viewMyReports(const string&);
void viewAssignedReports(const string& responderName);
void updateReportStatus();
void viewResponderActivity(const string& responderName);
void viewReports();
void updateReportPriority();
void searchReports();
void viewReportStatistics();
void deleteReport();
void addUser();
void viewUsersByRole();
void deleteUser();
string LoginUser(string role);
void preloadusers();
char ChoiceChecker(char minChoice, char maxChoice);
string getAvailableDispatcher();
string getAvailableResponder();

// Global variables to store data
vector<EmergencyReport> reports;
map<string, vector<User>> users;

int main()
{
    intro();
    preloadusers();
    while (true)
    {
        system("cls");
        cout << "=== User Type Selection ===\n" << endl;
        cout << "Please select your user type from the options below:" << endl;
        cout << "1. Chief Officer" << endl;
        cout << "2. Supervisor" << endl;
        cout << "3. Dispatcher" << endl;
        cout << "4. First Responder" << endl;
        cout << "5. Citizen" << endl;
        cout << "0. Exit" << endl;
        switch (ChoiceChecker('0', '5'))
        {
        case '1': ChiefOfficerMenu(); break;
        case '2': supervisorMenu(); break;
        case '3': dispatcherMenu(); break;
        case '4': firstResponderMenu(); break;
        case '5': citizenMenu(); break;
        case '0':
            cout << "\nThank you for using the Emergency Response System! Stay safe!" << endl;
            return 0;
        }
        system("pause");
    }
    return 0;
}
int intro()
{
    system("cls");
    cout << "==============================================================\n";
    cout << "             ______     _____         ______      \n";
    cout << "             | ____|    |  _ \\       /  ____\\     \n";
    cout << "             | |_       | |_) |      |  |____       \n";
    cout << "             |  _|      |  _ <       |______ \\      \n";
    cout << "             | |___     | | \\ \\       _____| |      \n";
    cout << "             |_____|    |_|  \\_\\     |_______|      \n";
    cout << "\n";
    cout << "==============================================================\n";
    cout << "        Welcome to the  Emergency Response System!\n";
    cout << "--------------------------------------------------------------\n";
    cout << "Your safety is our mission.\n";
    cout << "\nThis system empowers citizens and emergency staff to:\n";
    cout << "- Report emergencies quickly and safely\n";
    cout << "- Track and update the status of incidents\n";
    cout << "- Search and manage reports by location, name, or ID\n";
    cout << "- Ensure privacy and security for all users\n";
    cout << "\n";
    cout << "How it works:\n";
    cout << "* Citizens can submit and view their own reports.\n";
    cout << "* Dispatchers assign responders to emergencies.\n";
    cout << "* First Responders update emergency status and provide real-time response.\n";
    cout << "* Supervisors manage users, monitor operations, and ensure protocol compliance.\n";
    cout << "* The Chief has full control over the system, including oversight of all users,\n";
    cout << "  access to every report, and the authority to manage critical system operations.\n";
    cout << "\n";
    cout << "All roles require secure login and have role-based menu access.\n";
    cout << "Stay calm, stay safe, and let us help you in any emergency!\n";
    cout << "==============================================================\n\n";
    system("pause");
    return 0;
}
void ChiefOfficerMenu()
{
    string username = LoginUser("Chief");
    if (username == "") {
        cout << "Access Denied.\n";
        return;
    }
    while (true)
    {
        system("cls");
        cout << "=== Emergency Management System ===\n";
        cout << "Welcome, Chief Officer " << username << "!\n\n";
        cout << "----- Report Management -----\n";
        cout << "1. Add Emergency Report\n";
        cout << "2. View All Reports\n";
        cout << "3. Update Report Status\n";
        cout << "4. Update Report Priority\n";
        cout << "5. Search Reports\n";
        cout << "6. Delete Report\n\n";
        cout << "----- User Management -----\n";
        cout << "7. Add User\n";
        cout << "8. View Users by Role\n";
        cout << "9. Delete User\n\n";
        cout << "0. Logout\n";
        switch (ChoiceChecker('0', '9'))
        {
        case '1': addEmergencyReport("Chief " + username); break;
        case '2': viewReports(); break;
        case '3': updateReportStatus(); break;
        case '4': updateReportPriority(); break;
        case '5': searchReports(); break;
        case '6': deleteReport(); break;
        case '7': addUser(); break;
        case '8': viewUsersByRole(); break;
        case '9': deleteUser(); break;
        case '0':
            cout << "\nLogging out, Chief Officer " << username << "...\n";
            return;
        }
    }
}
void supervisorMenu()
{
    string username = LoginUser("Supervisor");
    if (username == "") {
        cout << "Access Denied.\n";
        return;
    }
    while (true)
    {
        system("cls");
        cout << "=== Emergency Management System ===\n";
        cout << "Welcome, " << username << "!\n\n";
        cout << "=== Supervisor Menu ===\n";
        cout << "1. View All Emergency Reports\n";
        cout << "2. Search Reports\n";
        cout << "3. View Report Statistics\n";
        cout << "4. Update Report Status\n";
        cout << "5. Update Report Priority\n";
        cout << "0. Logout\n";
        switch (ChoiceChecker('0', '5'))
        {
        case '1': viewReports(); break;
        case '2': searchReports(); break;
        case '3': viewReportStatistics(); break;
        case '4': updateReportStatus(); break;
        case '5': updateReportPriority(); break;
        case '0':
            cout << "\nLogging out, Supervisor " << username << "...\n";
            return;
        }
    }
}
void dispatcherMenu()
{
    string username = LoginUser("Dispatcher");
    if (username == "") {
        cout << "Access Denied.\n";
        return;
    }
    while (true)
    {
        system("cls");
        cout << "=== Emergency Management System ===\n";
        cout << "Welcome, Dispatcher " << username << "!\n\n";
        cout << "===== Dispatcher Menu =====\n";
        cout << "1. Add Emergency Report\n";
        cout << "2. View All Emergency Reports\n";
        cout << "3. Update Emergency Report Status\n";
        cout << "4. Update  Emergency Report Priority\n";
        cout << "5. Search Emergency Reports\n";
        cout << "0. Logout\n";
        switch (ChoiceChecker('0', '5'))
        {
        case '1': addEmergencyReport("Dispatcher " + username); break;
        case '2': viewReports(); break;
        case '3': updateReportStatus(); break;
        case '4': updateReportPriority(); break;
        case '5': searchReports(); break;
        case '0':
            cout << "\nLogging out, Dispatcher " << username << "...\n";
            return;
        }
    }
}
void firstResponderMenu()
{
    string username = LoginUser("Responder");
    if (username == "") {
        cout << "Access Denied.\n";
        return;
    }
    while (true)
    {
        system("cls");
        cout << "=== Emergency Management System ===\n";
        cout << "Welcome, " << username << "!\n\n";
        cout << "=== First Responder Menu ===\n\n";
        cout << "1. View Assigned Reports\n";
        cout << "2. Update Report Status\n";
        cout << "3. View My Activity Summary\n";
        cout << "0. Logout\n";
        switch (ChoiceChecker('0', '3'))
        {
        case '1':viewAssignedReports(username); break;
        case '2':updateReportStatus(); break;
        case '3':viewResponderActivity(username); break;
        case '4':
            cout << "\nLogging out, first Responder  " << username << "...\n";
            return;
        }
    }
}
void citizenMenu()
{
    string citizenName;
    system("cls");
    cout << "=== Citizen Menu ===\n" << endl;
    cout << "Please enter your name to continue: ";
    cin.ignore();
    getline(cin, citizenName);
    while (true)
    {
        system("cls");
        cout << "=== Citizen Menu (User: " << (citizenName.empty() ? "Unknown" : citizenName) << ") ===\n" << endl;
        cout << "1. Report Emergency" << endl;
        cout << "2. View My Reports" << endl;
        cout << "0. back" << endl;
        switch (ChoiceChecker('0', '2'))
        {
        case '1': addEmergencyReport(citizenName); break;
        case '2': viewMyReports(citizenName); break;
        case '0': return;
        }
    }
}
void addEmergencyReport(const string& citizenName)
{
    system("cls");
    EmergencyReport report;
    report.setID(reports.size() + 1);
    report.setIsActive(true);
    report.setPriority("High");
    report.setStatus("Reported");
    cout << "=== IERS Emergency Call ===\n" << endl;
    cout << "Are you:\n1. The person needing emergency (Victim)\n2. Witnessing the scene (Witness)\n3. Reporting for someone else (Other)\n ";
    switch (ChoiceChecker('1', '3'))
    {
    case '1':report.setReporterRole("Victim"); break;
    case '2':report.setReporterRole("Witness"); break;
    case '3':report.setReporterRole("Other"); break;
    default:report.setReporterRole("Unknown"); break;
    }
    system("cls");
    cout << "Enter incident Type:\n";
    cout << "1. Fire\n2. Medical Emergency\n3. Crime\n4. Accident\n5. Other\n ";
    char type = ChoiceChecker('0', '5');
    report.setType(type);
    switch (type)
    {
    case '1': report.setDepartment("FireFighter"); break;
    case '2': report.setDepartment("Medical"); break;
    case '3': report.setDepartment("Police"); break;
    case '4': report.setDepartment("Rescue"); break;
    case '5':report.setDepartment("Other"); break;
    default:report.setDepartment("Unknown"); break;

    }
    cin.ignore();
    cout << "Describe the emergency: ";
    string des;
    getline(cin, des);
    report.setDescription(des);
    cout << "Enter location: ";
    string loc;
    getline(cin, loc);
    report.setLocation(loc);
    if (!citizenName.empty())
    {
        report.setReporterName(citizenName);
    }
    else
    {
        string name;
        cout << "Enter your name: ";
        getline(cin, name);
        report.setReporterName(name);
    }
    report.setPatientOutcome("");
    report.setResponder(getAvailableResponder());
    report.setDispatcher(getAvailableDispatcher());
    report.setStatus("Dispatched");
    cout << "\nYour emergency has been reported. Help is on the way!" << endl;
    report.setReportedTime();
    reports.push_back(report);
    system("pause");
}
void viewMyReports(const string& citizenName)
{
    system("cls");
    cout << "=== My Emergency Reports ===\n" << endl;
    bool found = false;
    for (const EmergencyReport& report : reports)
    {
        if (report.getReporterName() == citizenName)
        {
            found = true;
            report.display();
        }
    }
    if (!found)
    {
        cout << "No reports found for your name." << endl;
    }
    system("pause");
}
void viewAssignedReports(const string& responderName) {
    system("cls");
    cout << "=== View Assigned Reports ===\n" << endl;
    bool found = false;
    for (const EmergencyReport& report : reports) {
        if (report.getResponder() == responderName) {
            report.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No reports assigned to you at the moment." << endl;
    }

    system("pause");
}
void updateReportStatus()
{
    system("cls");
    cout << "=== Update Report Status ===\n" << endl;
    cout << "Enter report ID: ";
    bool found = false;
    int id;
    cin >> id;
    cin.ignore();
    for (EmergencyReport& report : reports)
    {
        if (report.getId() == id)
        {
            found = true;
            cout << "Current status: " << report.getStatus() << endl;
            cout << "1. On the way\n2. Resolved\n3. Closed\n ";
            switch (ChoiceChecker('1', '3'))
            {
            case '1': report.setStatus("On the way"); break;
            case '2': {
                report.setStatus("Resolved");
                report.setResolvedTime();
                cout << "What happened to the patient or victim? " << endl;
                string outcome;
                cin.ignore();
                getline(cin, outcome);
                report.setPatientOutcome(outcome);
            }
                    break;
            case '3': report.setStatus("Closed"); report.setIsActive(false); break;
            }
            cout << "Report status updated successfully!" << endl;
            system("pause");
            return;

        }
    }
    if (!found)
        cout << "Report not found!" << endl;
    system("pause");
}
void viewResponderActivity(const string& responderName) {
    system("cls");
    cout << "=== Responder" << responderName << " Activity Summary == = \n" << endl;

    int total = 0, onTheWay = 0, resolved = 0, closed = 0;

    for (const EmergencyReport& report : reports) {
        if (report.getResponder() == responderName) {
            total++;

            string status = report.getStatus();
            if (status == "On the way") onTheWay++;
            else if (status == "Resolved") resolved++;
            else if (status == "Closed") closed++;
        }
    }

    if (total == 0) {
        cout << "No reports assigned to you yet.\n";
    }
    else {
        cout << "Responder: " << responderName << "\n";
        cout << "Total Reports Assigned: " << total << "\n";
        cout << " - On the Way: " << onTheWay << "\n";
        cout << " - Resolved: " << resolved << "\n";
        cout << " - Closed: " << closed << "\n";
        cout << "=== Resolved Reports Details ===\n\n";
        for (const EmergencyReport& report : reports) {
            if (report.getResponder() == responderName && report.getStatus() == "Resolved")
            {
                cout << "Report ID: " << report.getId() << "\n";
                cout << "  - Resolved Time: " << report.getResolvedTime() << "\n";
                cout << "  - Patient Outcome: " << report.getPatientOutcome() << "\n\n";

            }
        }
    }

    system("pause");
}
void viewReports()
{
    system("cls");
    cout << "=== View Emergency Reports ===\n" << endl;
    if (reports.empty())
    {
        cout << "No reports found." << endl;
        return;
    }
    for (const EmergencyReport& report : reports)
    {
        report.display();
    }

    system("pause");
    return;
}
void updateReportPriority()
{
    system("cls");
    cout << "=== Update Report Priority ===\n" << endl;
    cout << "Enter report ID: ";
    int id;
    cin >> id;
    cin.ignore();
    for (EmergencyReport& report : reports)
    {
        if (report.getId() == id)
        {

            cout << "Enter new priority (1-High, 2-Medium, 3-Low) ";
            switch (ChoiceChecker('1', '3'))
            {
            case '1':report.setPriority("High"); break;
            case '2':report.setPriority("Medium"); break;
            case '3':report.setPriority("Low"); break;
            }
            cout << "Report priority updated successfully!" << endl;
            return;
        }
    }

    cout << "Report not found!" << endl;
    system("pause");
}
void searchReports()
{
    system("cls");
    cout << "=== Search Reports ===\n" << endl;
    cout << "Search by:\n1. Location\n2. Citizen Name\n3. Report ID\n0. Back\n ";
    char searchType = ChoiceChecker('0', '3');
    cin.ignore();
    bool found = false;
    if (searchType == '1')
    {
        cout << "Enter location to search: ";
        string searchLocation;
        getline(cin, searchLocation);
        for (const EmergencyReport& report : reports)
        {
            if (report.getLocation() == searchLocation)
            {
                found = true;
                report.display();
                break;
            }
        }
    }
    else if (searchType == '2')
    {
        cout << "Enter citizen name to search: ";
        string searchName;
        getline(cin, searchName);
        for (const EmergencyReport& report : reports)
        {
            if (report.getReporterName() == searchName)
            {
                found = true;
                report.display();
                break;

            }
        }

    }
    else if (searchType == '3')
    {
        cout << "Enter report ID to search: ";
        int searchId;
        cin >> searchId;
        for (const EmergencyReport& report : reports)
        {
            if (report.getId() == searchId)
            {
                found = true;
                report.display();
                break;

            }
        }
    }
    else
        return;
    if (!found)
    {
        cout << "No reports found for your search." << endl;
    }
    system("pause");

}
void viewReportStatistics() {
    system("cls");
    cout << "=== Emergency Report Statistics ===\n" << endl;
    size_t total = reports.size();
    int pending = 0, inProgress = 0, resolved = 0;
    int high = 0, medium = 0, low = 0;
    map<string, int> responderCount;
    map<string, int> locationCount;
    map<string, int> typeCount;
    for (const EmergencyReport& report : reports) {
        string status = report.getStatus();
        string priority = report.getPriority();
        string responder = report.getResponder();
        string location = report.getLocation();
        string type = report.getType();
        // Status count
        if (status == "Pending") pending++;
        else if (status == "In Progress") inProgress++;
        else if (status == "Resolved") resolved++;
        // Priority count
        if (priority == "High") high++;
        else if (priority == "Medium") medium++;
        else if (priority == "Low") low++;
        // Count responders
        if (!responder.empty())
            responderCount[responder]++;
        // Count locations
        locationCount[location]++;
        // Count types
        typeCount[type]++;
    }
    cout << "Total Reports: " << total << "\n\n";
    cout << "Status Breakdown:\n";
    cout << " - Pending     : " << pending << endl;
    cout << " - In Progress : " << inProgress << endl;
    cout << " - Resolved    : " << resolved << endl;
    double resolvedPercent = (total > 0) ? (resolved * 100.0 / total) : 0;
    cout << "Resolved Percentage: " << resolvedPercent << "%\n\n";
    cout << "Priority Breakdown:\n";
    cout << " - High   : " << high << endl;
    cout << " - Medium : " << medium << endl;
    cout << " - Low    : " << low << "\n\n";
    // Most active responder
    string topResponder = "N/A";
    int maxReports = 0;
    for (auto& entry : responderCount) {
        if (entry.second > maxReports) {
            maxReports = entry.second;
            topResponder = entry.first;
        }
    }
    cout << "Most Active Responder: " << topResponder << " (" << maxReports << " reports)\n\n";
    // Location-wise report summary
    cout << "Reports per Location:\n";
    for (auto& loc : locationCount) {
        cout << " - " << loc.first << ": " << loc.second << " report(s)" << endl;
    }
    cout << "\nMost Common Emergency Types:\n";
    for (auto& t : typeCount) {
        cout << " - " << t.first << ": " << t.second << " report(s)" << endl;
    }
    cout << endl;
    system("pause");
}
void deleteReport() {
    system("cls");
    cout << "=== Delete Report ===\n" << endl;
    cout << "1. Delete report by ID\n";
    cout << "2. Delete all reports\n";
    cout << "0. Back\n";

    char choice = ChoiceChecker('0', '2');

    if (choice == '1') {
        // Delete single report by ID
        cout << "\nEnter report ID to delete: ";
        int id;
        cin >> id;
        cin.ignore();

        bool found = false;
        for (int i = 0; i < reports.size(); i++) {
            if (reports[i].getId() == id) {
                found = true;
                cout << "Are you sure you want to delete Report ID " << id << "? (y/n): ";
                char confirm;
                cin >> confirm;

                if (tolower(confirm) == 'y') {
                    reports.erase(reports.begin() + i);
                    cout << "Report deleted successfully.\n";
                }
                else {
                    cout << "Deletion cancelled.\n";
                }
                break;
            }
        }

        if (!found) {
            cout << "Report not found!" << endl;
        }
    }
    else if (choice == '2') {
        // Delete all reports
        if (reports.empty()) {
            cout << "\nNo reports to delete.\n";
        }
        else {
            cout << "\nAre you sure you want to delete ALL reports? (y/n): ";
            char confirm;
            cin >> confirm;
            if (tolower(confirm) == 'y') {
                reports.clear();
                cout << "All reports deleted successfully.\n";
            }
            else {
                cout << "Deletion cancelled.\n";
            }
        }
    }
    else
        return;

    system("pause");
}
void addUser() {
    system("cls");
    cout << "=== Add New User ===\n";
    cout << "Select the role for the new user:" << endl;
    cout << "1. Chief" << endl;
    cout << "2. Dispatcher" << endl;
    cout << "3. First Responder" << endl;
    cout << "4. Supervisor" << endl;
    cout << "0. Back" << endl;
    string role;
    switch (ChoiceChecker('0', '4')) {
    case '1': role = "Chief"; break;
    case '2': role = "Dispatcher"; break;
    case '3': role = "Responder"; break;
    case '4': role = "Supervisor"; break;
    case '0':return;
    }
    string username, password;
    cout << "Enter username for the new user: ";
    cin >> username;
    cin.ignore();
    for (const auto& u : users[role]) {
        if (u.name == username) {
            cout << "User already exists for this role!" << endl;
            return;
        }
    }
    cout << "Enter password for the new user: ";
    getline(cin, password);
    users[role].push_back({ username, password, role });
    cout << role << " User '" << username << "' added successfully!" << endl;
    system("pause");
}
void viewUsersByRole() {
    system("cls");
    cout << "=== View Users by Role ===\n\n";
    cout << "Select Role:\n";
    cout << "1. Chief\n";
    cout << "2. Dispatcher\n";
    cout << "3. First Responder\n";
    cout << "4. Supervisor\n";
    cout << "0. Back\n";

    string role;
    char choice = ChoiceChecker('0', '4');

    switch (choice) {
    case '1': role = "Chief"; break;
    case '2': role = "Dispatcher"; break;
    case '3': role = "Responder"; break;
    case '4': role = "Supervisor"; break;
    case '0': return;
    }

    bool found = false;
    cout << "\nUsers with role: " << role << "\n";
    cout << "-----------------------------\n";
    for (const auto& u : users[role]) {
        cout << " - " << u.name << " (" << u.role << ")\n";
        found = true;
    }
    if (!found) {
        cout << "No users found with role: " << role << "\n";
    }

    cout << endl;
    system("pause");
}
void deleteUser() {
    system("cls");
    cout << "=== Delete User ===\n" << endl;
    cout << "Select the role of the user you want to delete:" << endl;
    cout << "1. Dispatcher" << endl;
    cout << "2. Responder" << endl;
    cout << "3. Supervisor" << endl;
    char roleChoice = ChoiceChecker('1', '3');
    string role;
    switch (roleChoice) {
    case '1': role = "Dispatcher"; break;
    case '2': role = "Responder"; break;
    case '3': role = "Supervisor"; break;
    }
    vector<User>& roleUsers = users[role];
    if (roleUsers.empty()) {
        cout << "No users found in this role." << endl;
        system("pause");
        return;
    }
    cout << "\nUsers under role '" << role << "':" << endl;
    for (size_t i = 0; i < roleUsers.size(); ++i) {
        cout << i + 1 << ". " << roleUsers[i].name << endl;
    }
    int index;
    cout << "\nEnter the number of the user to delete: ";
    cin >> index;
    if (index < 1 || index > roleUsers.size()) {
        cout << "Invalid user number." << endl;
        system("pause");
        return;
    }
    string nameToDelete = roleUsers[index - 1].name;
    cout << "\nAre you sure you want to delete user '" << nameToDelete << "'? (y/n): ";
    char confirm;
    cin >> confirm;
    if (tolower(confirm) == 'y') {
        roleUsers.erase(roleUsers.begin() + index - 1);
        cout << "User '" << nameToDelete << "' deleted successfully." << endl;
    }
    else {
        cout << "Deletion cancelled." << endl;
    }
    system("pause");
}
string LoginUser(string role) {
    int chance = 0;
    while (chance < 3)
    {
        system("cls");
        string name, pass;
        cout << "--- " << role << " Login ---\n";
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Password: ";
        cin >> pass;

        for (const auto& u : users[role]) {
            if (u.name == name && u.password == pass) {
                cout << "Login Successful!\n";
                system("pause");
                return name;
            }
        }
        cout << "Invalid credentials.\n";
        chance++;
    }
    cout << "Out of chance....better luck next time";
    return "";
}
void preloadusers() {
    // Prevent duplicate users by clearing first
    users.clear();
    User Chief;
    Chief.name = "Irtaza";
    Chief.password = "pass123";
    Chief.role = "Chief";
    users["Chief"].push_back(Chief);
    User Supervisor;
    Supervisor.name = "Moiz"; // Consistent with earlier code
    Supervisor.password = "pass123";
    Supervisor.role = "Supervisor";
    users["Supervisor"].push_back(Supervisor);
    User Dispatcher;
    Dispatcher.name = "Sameer";
    Dispatcher.password = "pass123";
    Dispatcher.role = "Dispatcher";
    users["Dispatcher"].push_back(Dispatcher);
    User Responder;
    Responder.name = "Waqas";
    Responder.password = "pass123";
    Responder.role = "Responder";
    users["Responder"].push_back(Responder);
}

// Removed persistence function implementations

char ChoiceChecker(char minChoice, char maxChoice) {
    char choice;
    bool valid = false;

    do {
        cout << "choice: ";                                     
        cin >> choice;
        if (choice < minChoice || choice > maxChoice)
        {
            cout << "Invalid choice! Please try again.\n";
            system("cls");
        }
        else
        {
            valid = true;
        }
    } while (!valid);

    return choice;
}
string getAvailableDispatcher() {
    static int dIndex = 0;
    size_t size = users["Dispatcher"].size();
    if (size == 0) return "";

    dIndex = dIndex % size;  // Make sure index is always in valid range
    string name = users["Dispatcher"][dIndex].name;
    dIndex = (dIndex + 1) % size;  // Round-robin step
    return name;
}
string getAvailableResponder() {
    static int rIndex = 0;
    size_t size = users["Responder"].size();
    if (size == 0) return "";

    rIndex = rIndex % size;  // Fix: Prevent out-of-bounds if size changed
    string name = users["Responder"][rIndex].name;
    rIndex = (rIndex + 1) % size;// Round-robin step
    return name;
}
