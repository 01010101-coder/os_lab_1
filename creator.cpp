#include <iostream>
#include <fstream>
#include "creator.h"
#include "employee.h"

using namespace std;

void createBinaryFile(const char* filename, int recordCount) {
    ofstream outFile(filename, ios::binary);

    for (int i = 0; i < recordCount; ++i) {
        employee emp;

        cout << "Enter employee identification number: ";
        cin >> emp.num;
        cin.ignore();
        cout << "Enter employee name: ";
        cin.getline(emp.name, 10);
        cout << "Enter number of hours worked: ";
        cin >> emp.hours;

        outFile.write(reinterpret_cast<char*>(&emp), sizeof(emp));
    }

    outFile.close();
}