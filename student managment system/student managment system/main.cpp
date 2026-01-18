#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Maximum number of students we can store
const int MAX_STUDENTS = 100;

// Structure to store student information
struct Student {
    string enrollment;
    string name;
    string program;
    float totalFees;
    float paidFees;
    int semestersLeft;
    float gpa;
};

// Array to store all students
Student students[MAX_STUDENTS];
int studentCount = 0;  // To keep track of how many students we have

// Function to save data to file
void saveToFile() {
    ofstream file("students.txt");

    for (int i = 0; i < studentCount; i++) {
        file << students[i].enrollment << ","
            << students[i].name << ","
            << students[i].program << ","
            << students[i].totalFees << ","
            << students[i].paidFees << ","
            << students[i].semestersLeft << ","
            << students[i].gpa << endl;
    }

    file.close();
}

// Function to load data from file
void loadFromFile() {
    ifstream file("students.txt");

    if (!file) {
        cout << "No previous data found. Starting fresh.\n";
        return;
    }

    studentCount = 0;  // Reset counter

    string line;
    while (studentCount < MAX_STUDENTS && getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);
        size_t pos5 = line.find(',', pos4 + 1);
        size_t pos6 = line.find(',', pos5 + 1);

        // Extract data from each position
        students[studentCount].enrollment = line.substr(0, pos1);
        students[studentCount].name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        students[studentCount].program = line.substr(pos2 + 1, pos3 - pos2 - 1);
        students[studentCount].totalFees = stof(line.substr(pos3 + 1, pos4 - pos3 - 1));
        students[studentCount].paidFees = stof(line.substr(pos4 + 1, pos5 - pos4 - 1));
        students[studentCount].semestersLeft = stoi(line.substr(pos5 + 1, pos6 - pos5 - 1));
        students[studentCount].gpa = stof(line.substr(pos6 + 1));

        studentCount++;
    }

    file.close();
    cout << "Data loaded successfully! Total students: " << studentCount << endl;
}

// Function to add a new student
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "\nCannot add more students! Maximum limit reached.\n";
        return;
    }

    Student newStudent;

    cout << "\n========== ADD NEW STUDENT ==========\n";

    cout << "Enter Enrollment Number: ";
    cin >> newStudent.enrollment;

    // Check if enrollment already exists
    for (int i = 0; i < studentCount; i++) {
        if (students[i].enrollment == newStudent.enrollment) {
            cout << "\nError: Enrollment number already exists!\n";
            return;
        }
    }

    cout << "Enter Student Name: ";
    cin.ignore();  // To clear the input buffer
    getline(cin, newStudent.name);

    cout << "Enter Program of Study: ";
    getline(cin, newStudent.program);

    cout << "Enter Total Fees: $";
    cin >> newStudent.totalFees;

    cout << "Enter Paid Fees: $";
    cin >> newStudent.paidFees;

    cout << "Enter Semesters Left: ";
    cin >> newStudent.semestersLeft;

    cout << "Enter Current GPA (0.0 to 4.0): ";
    cin >> newStudent.gpa;

    // Validate GPA
    if (newStudent.gpa < 0 || newStudent.gpa > 4.0) {
        cout << "\nInvalid GPA! Must be between 0.0 and 4.0\n";
        return;
    }

    // Add the student to our array
    students[studentCount] = newStudent;
    studentCount++;

    // Save to file
    saveToFile();

    cout << "\nStudent added successfully!\n";
}

// Function to display a student's details
void displayStudent() {
    if (studentCount == 0) {
        cout << "\nNo students in the system!\n";
        return;
    }

    string searchEnrollment;

    cout << "\n========== VIEW STUDENT DETAILS ==========\n";
    cout << "Enter Enrollment Number to search: ";
    cin >> searchEnrollment;

    bool found = false;

    // Search for the student
    for (int i = 0; i < studentCount; i++) {
        if (students[i].enrollment == searchEnrollment) {
            found = true;

            // Calculate pending fees
            float pendingFees = students[i].totalFees - students[i].paidFees;

            // Display all details
            cout << "\n========== STUDENT DETAILS ==========\n";
            cout << "Enrollment Number: " << students[i].enrollment << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Program: " << students[i].program << endl;
            cout << "Total Fees: $" << students[i].totalFees << endl;
            cout << "Paid Fees: $" << students[i].paidFees << endl;
            cout << "Pending Fees: $" << pendingFees << endl;
            cout << "Semesters Left: " << students[i].semestersLeft << endl;
            cout << "GPA: " << students[i].gpa << endl;
            cout << "======================================\n";

            break;
        }
    }

    if (!found) {
        cout << "\nStudent not found with Enrollment Number: " << searchEnrollment << endl;
    }
}

// Function to display all students
void displayAllStudents() {
    if (studentCount == 0) {
        cout << "\nNo students in the system!\n";
        return;
    }

    cout << "\n========== ALL STUDENTS ==========\n";
    cout << "Total Students: " << studentCount << "\n\n";

    for (int i = 0; i < studentCount; i++) {
        cout << (i + 1) << ". " << students[i].name
            << " (" << students[i].enrollment << ") - "
            << students[i].program << endl;
    }
}

// Function to update student fees
void updateFees() {
    if (studentCount == 0) {
        cout << "\nNo students in the system!\n";
        return;
    }

    string searchEnrollment;
    float payment;

    cout << "\n========== UPDATE FEES ==========\n";
    cout << "Enter Enrollment Number: ";
    cin >> searchEnrollment;

    bool found = false;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].enrollment == searchEnrollment) {
            found = true;

            float pendingFees = students[i].totalFees - students[i].paidFees;

            cout << "\nStudent: " << students[i].name << endl;
            cout << "Total Fees: $" << students[i].totalFees << endl;
            cout << "Already Paid: $" << students[i].paidFees << endl;
            cout << "Pending Fees: $" << pendingFees << endl;

            if (pendingFees <= 0) {
                cout << "\nNo pending fees!\n";
                return;
            }

            cout << "\nEnter payment amount: $";
            cin >> payment;

            if (payment > 0 && payment <= pendingFees) {
                students[i].paidFees += payment;

                // Save to file after update
                saveToFile();

                cout << "\nPayment successful!\n";
                cout << "Updated paid fees: $" << students[i].paidFees << endl;
                cout << "Remaining fees: $" << (students[i].totalFees - students[i].paidFees) << endl;
            }
            else {
                cout << "\nInvalid payment amount!\n";
                cout << "Please enter amount between $0.01 and $" << pendingFees << endl;
            }

            break;
        }
    }

    if (!found) {
        cout << "\nStudent not found!\n";
    }
}

// Function to update GPA
void updateGPA() {
    if (studentCount == 0) {
        cout << "\nNo students in the system!\n";
        return;
    }

    string searchEnrollment;
    float newGPA;

    cout << "\n========== UPDATE GPA ==========\n";
    cout << "Enter Enrollment Number: ";
    cin >> searchEnrollment;

    bool found = false;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].enrollment == searchEnrollment) {
            found = true;

            cout << "\nStudent: " << students[i].name << endl;
            cout << "Current GPA: " << students[i].gpa << endl;

            cout << "Enter new GPA (0.0 to 4.0): ";
            cin >> newGPA;

            if (newGPA >= 0 && newGPA <= 4.0) {
                students[i].gpa = newGPA;

                // Save to file after update
                saveToFile();

                cout << "\nGPA updated successfully!\n";
            }
            else {
                cout << "\nInvalid GPA! Must be between 0.0 and 4.0\n";
            }

            break;
        }
    }

    if (!found) {
        cout << "\nStudent not found!\n";
    }
}

// Function to search student by name
void searchStudent() {
    if (studentCount == 0) {
        cout << "\nNo students in the system!\n";
        return;
    }

    string searchName;

    cout << "\n========== SEARCH STUDENT ==========\n";
    cout << "Enter Student Name to search: ";
    cin.ignore();
    getline(cin, searchName);

    bool found = false;

    cout << "\nSearch Results:\n";
    for (int i = 0; i < studentCount; i++) {
        if (students[i].name.find(searchName) != string::npos) {
            found = true;
            cout << "\n" << (i + 1) << ". " << students[i].name
                << " (" << students[i].enrollment << ") - "
                << students[i].program << endl;
            cout << "   GPA: " << students[i].gpa
                << ", Pending Fees: $" << (students[i].totalFees - students[i].paidFees) << endl;
        }
    }

    if (!found) {
        cout << "\nNo students found with name containing: " << searchName << endl;
    }
}

// Function to show main menu
void showMenu() {
    cout << "\n========== STUDENT MANAGEMENT SYSTEM ==========\n";
    cout << "1. Add New Student\n";
    cout << "2. View Student Details (by Enrollment)\n";
    cout << "3. View All Students\n";
    cout << "4. Update Fees Payment\n";
    cout << "5. Update GPA\n";
    cout << "6. Search Student by Name\n";
    cout << "7. Exit\n";
    cout << "================================================\n";
    cout << "Enter your choice (1-7): ";
}

// Main function
int main() {
    int choice;

    cout << "========================================\n";
    cout << "  WELCOME TO STUDENT MANAGEMENT SYSTEM\n";
    cout << "========================================\n\n";

    // Load data from file when program starts
    loadFromFile();

    // Main program loop
    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudent();
            break;
        case 3:
            displayAllStudents();
            break;
        case 4:
            updateFees();
            break;
        case 5:
            updateGPA();
            break;
        case 6:
            searchStudent();
            break;
        case 7:
            // Save data before exiting
            saveToFile();
            cout << "\nThank you for using Student Management System!\n";
            cout << "All data has been saved to file.\n";
            cout << "Goodbye!\n";
            return 0;
        default:
            cout << "\nInvalid choice! Please enter 1-7.\n";
        }
    }

    return 0;
}