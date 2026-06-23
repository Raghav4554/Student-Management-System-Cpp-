#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    int age;
    string course;

    void input() {
        cout << "Enter Roll Number: ";
        cin >> rollNo;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() {
        cout << "\nRoll No: " << rollNo;
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nCourse: " << course << endl;
    }
};

void addStudent() {
    Student s;

    ofstream file("students.txt", ios::app);

    s.input();

    file << s.rollNo << "|"
         << s.name << "|"
         << s.age << "|"
         << s.course << endl;

    file.close();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents() {
    ifstream file("students.txt");

    string line;

    cout << "\n----- Student Records -----\n";

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void searchStudent() {
    ifstream file("students.txt");

    int roll;
    cout << "Enter Roll Number to Search: ";
    cin >> roll;

    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos = line.find("|");

        int storedRoll = stoi(line.substr(0, pos));

        if (storedRoll == roll) {
            cout << "\nRecord Found:\n";
            cout << line << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nStudent Not Found!\n";

    file.close();
}

void updateStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    int roll;
    cout << "Enter Roll Number to Update: ";
    cin >> roll;

    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos = line.find("|");
        int storedRoll = stoi(line.substr(0, pos));

        if (storedRoll == roll) {
            Student s;

            cout << "\nEnter New Details:\n";
            s.input();

            temp << s.rollNo << "|"
                 << s.name << "|"
                 << s.age << "|"
                 << s.course << endl;

            found = true;
        }
        else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nRecord Updated Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

void deleteStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    int roll;
    cout << "Enter Roll Number to Delete: ";
    cin >> roll;

    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos = line.find("|");
        int storedRoll = stoi(line.substr(0, pos));

        if (storedRoll == roll) {
            found = true;
        }
        else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nRecord Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n========== Student Management System ==========\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
