#include <iostream>
#include <fstream>
#include <limits>
#include "creator.h"
#include "employee.h"

using namespace std;

void createBinaryFile(const char* filename, int recordCount) {
    ofstream outFile(filename, ios::binary);

    for (int i = 0; i < recordCount; ++i) {
        employee emp;

        cout << "Enter employee identification number: ";
        while (!(cin >> emp.num)) {
            cout << "Invalid input! Please enter a valid integer for employee number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter employee name (max 9 characters): ";
        cin.getline(emp.name, 10);

        while (emp.name[0] == '\0') {
            cout << "Name cannot be empty! Please enter a valid name: ";
            cin.getline(emp.name, 10);
        }

        cout << "Enter number of hours worked: ";
        while (!(cin >> emp.hours) || emp.hours < 0) {
            cout << "Invalid input! Please enter a valid number of hours worked (positive value): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        outFile.write(reinterpret_cast<char*>(&emp), sizeof(emp));
    }

    outFile.close();
}
