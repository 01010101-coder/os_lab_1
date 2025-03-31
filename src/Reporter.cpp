/* Reporter.cpp */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include "employee.h"

// Структура для отчета о сотруднике
struct EmployeeReport {
    employee emp;
    double salary;
};

// Чтение данных из бинарного файла
bool readBinaryFile(const std::string &fileName, double hourlyRate, std::vector<EmployeeReport> &reports) {
    std::ifstream ifs(fileName, std::ios::binary);
    if (!ifs) {
        std::cerr << "Cannot open binary file: " << fileName << std::endl;
        return false;
    }

    employee emp;
    while (ifs.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        reports.push_back(EmployeeReport{ emp, emp.hours * hourlyRate });
    }

    ifs.close();
    return true;
}

// Сортировка сотрудников по номеру
void sortReports(std::vector<EmployeeReport> &reports) {
    std::sort(reports.begin(), reports.end(), [](const EmployeeReport& a, const EmployeeReport& b) {
        return a.emp.num < b.emp.num;
    });
}

// Запись отчета в текстовый файл
bool writeReportFile(const std::string &reportFileName, const std::string &sourceFileName, const std::vector<EmployeeReport> &reports) {
    std::ofstream ofs(reportFileName);
    if (!ofs) {
        std::cerr << "Cannot open report file: " << reportFileName << std::endl;
        return false;
    }

    ofs << "Report for file \"" << sourceFileName << "\"\n";
    ofs << "Num\tName\tHours\tSalary\n";

    for (const auto& er : reports) {
        ofs << er.emp.num << "\t" << er.emp.name << "\t"
            << er.emp.hours << "\t" << std::fixed << std::setprecision(2)
            << er.salary << "\n";
    }

    ofs.close();
    return true;
}

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc != 4) {
        std::cerr << "Usage: Reporter <binary_file> <report_file> <hourly_rate>" << std::endl;
        return 1;
    }

    std::string binFileName = argv[1];
    std::string reportFileName = argv[2];
    double hourlyRate = 0.0;

    // Преобразование ставки оплаты
    try {
        hourlyRate = std::stod(argv[3]);
    } catch (...) {
        std::cerr << "Invalid hourly rate" << std::endl;
        return 1;
    }

    std::vector<EmployeeReport> reports;

    // Чтение, сортировка и запись отчета
    if (!readBinaryFile(binFileName, hourlyRate, reports)) return 1;
    sortReports(reports);
    if (!writeReportFile(reportFileName, binFileName, reports)) return 1;

    return 0;
}
