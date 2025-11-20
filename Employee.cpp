#include "Employee.h"
#include "Console.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

//Validation 
bool isValidAge(int age){ return age>0 && age<120; }
bool isValidSalary(double salary){ return salary>=0; }
bool isValidGender(const string &gender){ return gender=="M"||gender=="F"||gender=="m"||gender=="f"; }
bool isValidEmail(const string &email){ return email.find('@')!=string::npos && email.find('.')!=string::npos; }

// Add Employee
void addEmployee(){
    if(employeeCount>=MAX_EMPLOYEES){
        console::clearScreen();
        cout << "Employee list is full!\n";
        console::delayMs(1000);
        return;
    }

    bool addMore = true;
    while(addMore && employeeCount<MAX_EMPLOYEES){
        Employee emp;
        console::clearScreen();
        console::setColorHeader();
        cout << "===== ADD NEW EMPLOYEE =====\n\n";
        console::resetColor();

        // Name
        do{
            cout << "Name: "; getline(cin, emp.name);
            if(emp.name.empty()) cout<<"Name cannot be empty.\n";
        } while(emp.name.empty());

        // Age
        bool valid=false;
        while(!valid){
            cout << "Age: "; cin >> emp.age;
            if(cin.fail() || !isValidAge(emp.age)){
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout<<"Invalid age! Must be 1-119.\n";
            } else { cin.ignore(numeric_limits<streamsize>::max(),'\n'); valid=true; }
        }

        // Gender
        valid=false;
        while(!valid){
            cout << "Gender (M/F): "; cin >> emp.gender;
            if(!isValidGender(emp.gender)) cout<<"Invalid! Enter M or F.\n";
            else { cin.ignore(numeric_limits<streamsize>::max(),'\n'); valid=true; }
        }

        // Position
        cout << "Position: "; getline(cin, emp.position);

        // Salary
        valid=false;
        while(!valid){
            cout << "Salary: "; cin >> emp.salary;
            if(cin.fail() || !isValidSalary(emp.salary)){
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout<<"Invalid salary! Must >=0.\n";
            } else { cin.ignore(numeric_limits<streamsize>::max(),'\n'); valid=true; }
        }

        // Email
        valid=false;
        while(!valid){
            cout << "Email: "; cin >> emp.email;
            if(!isValidEmail(emp.email)) cout<<"Invalid! Must contain '@' and '.'\n";
            else { cin.ignore(numeric_limits<streamsize>::max(),'\n'); valid=true; }
        }

        employees[employeeCount++] = emp;

        char choice='n';
        cout << "\nAdd another employee? (y/n): ";
        cin >> choice; cin.ignore(numeric_limits<streamsize>::max(),'\n');
        addMore = (choice=='y' || choice=='Y');
    }
}

// Display Employees
void displayEmployees(){
    console::clearScreen();
    console::setColorHeader();
    cout << "===== EMPLOYEE LIST =====\n\n";
    console::resetColor();

    if(employeeCount==0){
        cout << "No employees found.\nPress Backspace to return...";
        console::readKey();
        return;
    }

    // Header
    cout << left
         << setw(20) << "Name"
         << setw(5)  << "Age"
         << setw(8)  << "Gender"
         << setw(15) << "Position"
         << setw(12) << "Salary"
         << setw(25) << "Email\n";
    cout << string(85,'-') << "\n";

    // Rows
    for(int i=0;i<employeeCount;i++){
        Employee &e = employees[i];
        cout << setw(20)<<e.name
             << setw(5)<<e.age
             << setw(8)<<e.gender
             << setw(15)<<e.position
             << setw(12)<<fixed<<setprecision(2)<<e.salary
             << setw(25)<<e.email
             << "\n";
    }

    cout << "\nPress Backspace or Enter to return...";
    console::readKey();
}
