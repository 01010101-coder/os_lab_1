#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // для std::system
#include "employee.h"

// Вывод содержимого бинарного файла
void printBinaryFile(const std::string& fileName) {
    std::ifstream ifs(fileName, std::ios::binary);
    if (!ifs) {
        std::cerr << "Error opening binary file: " << fileName << std::endl;
        return;
    }

    employee emp;
    while (ifs.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        std::cout << "Num: " << emp.num
                  << " Name: " << emp.name
                  << " Hours: " << emp.hours << std::endl;
    }
}

// Вывод содержимого текстового отчета
void printReportFile(const std::string& fileName) {
    std::ifstream ifs(fileName);
    if (!ifs) {
        std::cerr << "Error opening report file: " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        std::cout << line << std::endl;
    }
}

int main() {
    std::string binFileName;
    int recordCount = 0;

    std::cout << "Binary file name: ";
    std::cin >> binFileName;
    std::cout << "Number of records: ";
    std::cin >> recordCount;

    // Формируем и запускаем команду Creator
    std::string creatorCmd = "./src/Creator " + binFileName + " " + std::to_string(recordCount);
    int creatorStatus = std::system(creatorCmd.c_str());
    if (creatorStatus != 0) {
        std::cerr << "Creator process failed." << std::endl;
        return 1;
    }

    // Печатаем содержимое бинарного файла
    printBinaryFile(binFileName);

    std::string reportFileName;
    double hourlyRate;

    std::cout << "Report file name: ";
    std::cin >> reportFileName;
    std::cout << "Hourly rate: ";
    std::cin >> hourlyRate;

    // Формируем и запускаем команду Reporter
    std::string reporterCmd = "./src/Reporter " + binFileName + " " + reportFileName + " " + std::to_string(hourlyRate);
    int reporterStatus = std::system(reporterCmd.c_str());
    if (reporterStatus != 0) {
        std::cerr << "Reporter process failed." << std::endl;
        return 1;
    }

    // Печатаем содержимое файла отчета
    printReportFile(reportFileName);

    return 0;
}
