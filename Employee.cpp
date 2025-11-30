#include "Employee.h"
#include "Console.h"
#include "Validation.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;
using namespace console;

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

// ADD EMPLOYEE
void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        clearScreen();
        cout << "Employee list is full!\n";
        delayMs(1000);
        return;
    }

    bool addMore = true;

    while (addMore && employeeCount < MAX_EMPLOYEES) {

        Employee emp;
        clearScreen();
        setColorHeader();
        cout << "===== ADD NEW EMPLOYEE =====\n\n";
        resetColor();

        //NAME 
        do {
            cout << "Name: ";
            getline(cin, emp.name);

            if (!isValidName(emp.name))
                cout << "Invalid name! Only letters and spaces allowed.\n";

        } while (!isValidName(emp.name));



        // AGE 
        bool valid = false;
        while (!valid) {
            string input;
            cout << "Age: ";
            getline(cin, input);

            if (input.empty()) {
                cout << "You entered nothing! Please enter a number.\n";
                continue;
            }

            bool allDigits = true;
            for (char c : input)
                if (!isdigit(c))
                 allDigits = false;

            if (!allDigits) {
                cout << "Invalid age! Numbers only.\n";
                continue;
            }

            int age = stoi(input);
            if (!isValidAge(age)) {
                cout << "Invalid age! Must be 1-119.\n";
                continue;
            }

            emp.age = age;
            valid = true;
        }



        // GENDER
        valid = false;
        while (!valid) {
            string input;
            cout << "Gender (M/F): ";
            getline(cin, input);

            if (input.empty()) {
                cout << "You entered nothing! Please enter M or F.\n";
                continue;
            }

            if (input.size() != 1 || !isValidGender(input[0])) {
                cout << "Invalid! Enter M or F.\n";
                continue;
            }

            emp.gender = input[0];
            valid = true;
        }



        // POSITION
        do {
            cout << "Position: ";
            getline(cin, emp.position);

            if (emp.position.empty())
                cout << "Position cannot be empty.\n";

        } while (emp.position.empty());



        // SALARY 
        valid = false;
        while (!valid) {
            string input;
            cout << "Salary: ";
            getline(cin, input);

            if (input.empty()) {
                cout << "You entered nothing! Please enter a number.\n";
                continue;
            }

            int dotCount = 0;
            bool validNumber = true;

            for (char c : input) {
                if (!isdigit(c) && c != '.') validNumber = false;
                if (c == '.') dotCount++;
                if (dotCount > 1) validNumber = false;
            }

            if (!validNumber) {
                cout << "Invalid salary! Must be a number.\n";
                continue;
            }

            double sal = stod(input);

            if (!isValidSalary(sal)) {
                cout << "Salary must be >= 0.\n";
                continue;
            }

            emp.salary = sal;
            valid = true;
        }



        //  EMAIL 
        valid = false;
        while (!valid) {
            string input;
            cout << "Email: ";
            getline(cin, input);

            if (input.empty()) {
                cout << "You entered nothing! Please enter an email.\n";
                continue;
            }

            if (!isValidEmail(input)) {
                cout << "Invalid email! Must contain '@' and '.'.\n";
                continue;
            }

            emp.email = input;
            valid = true;
        }



        //  SAVE EMPLOYEE 
        employees[employeeCount++] = emp;

        char choice = 'n';
        cout << "\nAdd another employee? (y/n): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        addMore = (choice == 'y' || choice == 'Y');
    }
}



// DISPLAY EMPLOYEES
void displayEmployees() {
    clearScreen();
    setColorHeader();
    cout << "===== EMPLOYEE LIST =====\n\n";
    resetColor();

    if (employeeCount == 0) {
        cout << "No employees found.\nPress Backspace to return...";
        readKey();
        return;
    }

    // HEADER
    cout << left
         << setw(20) << "Name"
         << setw(5)  << "Age"
         << setw(8)  << "Gender"
         << setw(15) << "Position"
         << setw(12) << "Salary"
         << setw(25) << "Email\n";

    cout << string(85, '-') << "\n";

    // ROWS
    for (int i = 0; i < employeeCount; i++) {
        Employee &e = employees[i];

        cout << setw(20) << e.name
             << setw(5)  << e.age
             << setw(8)  << e.gender
             << setw(15) << e.position
             << setw(12) << fixed << setprecision(2) << e.salary
             << setw(25) << e.email
             << "\n";
    }

    cout << "\nPress Backspace or Enter to return...";
    readKey();
}
