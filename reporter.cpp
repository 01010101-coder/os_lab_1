#include <fstream>
#include "reporter.h"
#include "employee.h"
#include <iostream>

using namespace std;

void createReport(const char* binaryFilename, const char* reportFilename, double hourlyRate) {
    ifstream inFile(binaryFilename, ios::binary);
    if (!inFile) {
        cerr << "Error: Unable to open the binary file " << binaryFilename << endl;
        return;
    }

    ofstream outFile(reportFilename);
    if (!outFile) {
        cerr << "Error: Unable to open the report file " << reportFilename << endl;
        inFile.close();
        return;
    }

    outFile << "Report for file " << binaryFilename << "\n";
    outFile << "Employee number, Employee name, Hours worked, Salary\n";

    employee emp = {};
    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        if (emp.name[0] == '\0') {
            cerr << "Warning: Employee " << emp.num << " has an empty name. Skipping this entry." << endl;
            continue;
        }

        if (emp.hours < 0) {
            cerr << "Warning: Employee " << emp.num << " has invalid hours worked (" << emp.hours << "). Skipping this entry." << endl;
            continue;
        }

        double salary = emp.hours * hourlyRate;

        outFile << emp.num << ", " << emp.name << ", " << emp.hours << ", " << salary << "\n";
    }

    inFile.close();
    outFile.close();
}
