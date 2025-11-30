#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
using namespace std;

struct Employee {
    string name;
    int age;
    char gender;
    string position;
    double salary;
    string email;
};

const int MAX_EMPLOYEES = 100;

extern Employee employees[MAX_EMPLOYEES];
extern int employeeCount;

void addEmployee();
void displayEmployees();

#endif
