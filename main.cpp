#include <iostream>
#include <fstream>
#include "creator.h"
#include "reporter.h"
#include "employee.h"

using namespace std;

int main() {
    char binaryFile[100], reportFile[100];
    int recordCount;
    double hourlyRate;

    cout << "Enter the name of the binary file: ";
    cin >> binaryFile;
    cout << "Enter the number of records in the file: ";
    cin >> recordCount;

    createBinaryFile(binaryFile, recordCount);

    ifstream inFile(binaryFile, ios::binary);
    employee emp = {};
    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        cout << emp.num << ", " << emp.name << ", " << emp.hours << "\n";
    }
    inFile.close();

    cout << "Enter the name of the report file: ";
    cin >> reportFile;
    cout << "Enter the hourly wage: ";
    cin >> hourlyRate;

    createReport(binaryFile, reportFile, hourlyRate);

    ifstream reportIn(reportFile);
    char line[256];
    while (reportIn.getline(line, sizeof(line))) {
        cout << line << "\n";
    }

    return 0;
}
