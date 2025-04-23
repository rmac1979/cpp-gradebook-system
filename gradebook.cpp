/*
Author: Ryan McCamy
Assignment: Gradebook System
Description:Program allows a teacher to input, sort, search, and analyze student grades. */
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 100;

void inputStudents(string names[], int grades[], int &count);
void sortGrades(string names[], int grades[], int count, bool ascending);
int searchStudent(const string names[], int grades[], int count, string target);
void calculateStatistics(const int grades[], int count);
void displayAll(const string names[], const int grades[], int count);
char getLetterGrade(int grade);
void editGrade(string names[], int grades[], int count);

int main() {
    string studentNames[MAX_STUDENTS];
    int studentGrades[MAX_STUDENTS];
    int studentCount = 0;
    bool dataEntered = false;

    int choice;
    do {
        cout << "\n--- Gradebook Menu ---\n";
        cout << "1. Enter Student Data\n";
        cout << "2. Display All Grades\n";
        cout << "3. Sort Grades\n";
        cout << "4. Search for a Student\n";
        cout << "5. Class Statistics\n";
        cout << "6. Edit a Student's Grade\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inputStudents(studentNames, studentGrades, studentCount);
                dataEntered = true;
                break;
            case 2:
                if (dataEntered) displayAll(studentNames, studentGrades, studentCount);
                else cout << "Please enter student data first.\n";
                break;
            case 3:
                if (dataEntered) {
                    int sortChoice;
                    cout << "1. Ascending\n2. Descending\nChoose sort order: ";
                    cin >> sortChoice;
                    sortGrades(studentNames, studentGrades, studentCount, sortChoice == 1);
                    cout << "Grades sorted.\n";
                } else {
                    cout << "Please enter student data first.\n";
                }
                break;
            case 4:
                if (dataEntered) {
                    string name;
                    cout << "Enter student name to search: ";
                    cin >> ws;
                    getline(cin, name);
                    int index = searchStudent(studentNames, studentGrades, studentCount, name);
                    if (index != -1) {
                        cout << name << "'s grade: " << studentGrades[index]
                             << " (" << getLetterGrade(studentGrades[index]) << ")\n";
                    } else {
                        cout << "Student not found.\n";
                    }
                } else {
                    cout << "Please enter student data first.\n";
                }
                break;
            case 5:
                if (dataEntered) calculateStatistics(studentGrades, studentCount);
                else cout << "Please enter student data first.\n";
                break;
            case 6:
                if (dataEntered) editGrade(studentNames, studentGrades, studentCount);
                else cout << "Please enter student data first.\n";
                break;
            case 7:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}

void inputStudents(string names[], int grades[], int &count) {
    cout << "Enter the number of students: ";
    cin >> count;
    for (int i = 0; i < count; ++i) {
        cout << "Enter student name: ";
        cin >> ws;
        getline(cin, names[i]);
        cout << "Enter " << names[i] << "'s grade: ";
        cin >> grades[i];
    }
}

void sortGrades(string names[], int grades[], int count, bool ascending) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if ((ascending && grades[i] > grades[j]) || (!ascending && grades[i] < grades[j])) {
                swap(grades[i], grades[j]);
                swap(names[i], names[j]);
            }
        }
    }
}

int searchStudent(const string names[], int grades[], int count, string target) {
    for (int i = 0; i < count; ++i) {
        if (names[i] == target) return i;
    }
    return -1;
}

void calculateStatistics(const int grades[], int count) {
    int sum = 0, max = grades[0], min = grades[0];
    for (int i = 0; i < count; ++i) {
        sum += grades[i];
        if (grades[i] > max) max = grades[i];
        if (grades[i] < min) min = grades[i];
    }
    double average = static_cast<double>(sum) / count;
    cout << fixed << setprecision(2);
    cout << "Average Grade: " << average << "\n";
    cout << "Highest Grade: " << max << "\n";
    cout << "Lowest Grade: " << min << "\n";
}

void displayAll(const string names[], const int grades[], int count) {
    cout << "\nStudent Grades:\n";
    for (int i = 0; i < count; ++i) {
        cout << names[i] << ": " << grades[i] << " (" << getLetterGrade(grades[i]) << ")\n";
    }
}

char getLetterGrade(int grade) {
    if (grade >= 90) return 'A';
    else if (grade >= 80) return 'B';
    else if (grade >= 70) return 'C';
    else if (grade >= 60) return 'D';
    else return 'F';
}

void editGrade(string names[], int grades[], int count) {
    string name;
    cout << "Enter the student name to edit grade: ";
    cin >> ws;
    getline(cin, name);
    int index = searchStudent(names, grades, count, name);
    if (index != -1) {
        cout << "Current grade for " << name << ": " << grades[index] << "\n";
        cout << "Enter new grade: ";
        cin >> grades[index];
        cout << "Grade updated.\n";
    } else {
        cout << "Student not found.\n";
    }
}
