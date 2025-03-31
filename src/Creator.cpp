/* Creator.cpp */
#include <iostream>
#include <fstream>
#include <string>
#include "employee.h"

// Функция для ввода данных сотрудника
bool inputEmployeeData(employee &emp, int index) {
    std::cout << "Enter employee " << index + 1 << " (num name hours): ";
    if (!(std::cin >> emp.num >> emp.name >> emp.hours)) {
        std::cerr << "Input error" << std::endl;
        return false;
    }
    return true;
}

// Функция для создания бинарного файла
bool createBinaryFile(const std::string &fileName, int recordCount) {
    std::ofstream ofs(fileName, std::ios::binary);
    if (!ofs) {
        std::cerr << "Cannot open file for writing: " << fileName << std::endl;
        return false;
    }

    // Цикл для ввода и записи данных о сотрудниках
    for (int i = 0; i < recordCount; ++i) {
        employee emp = {};
        if (!inputEmployeeData(emp, i)) {
            return false;
        }

        // Запись данных в бинарный файл
        ofs.write(reinterpret_cast<char*>(&emp), sizeof(emp));
        if (!ofs) {
            std::cerr << "Write error" << std::endl;
            return false;
        }
    }

    ofs.close();
    return true;
}

int main(int argc, char* argv[]) {
    // Проверка на правильность аргументов командной строки
    if (argc != 3) {
        std::cerr << "Usage: Creator <binary_file> <record_count>" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    int recordCount = 0;

    // Преобразование количества записей в целое число
    try {
        recordCount = std::stoi(argv[2]);
    } catch (...) {
        std::cerr << "Invalid record count" << std::endl;
        return 1;
    }

    // Создание бинарного файла с записями сотрудников
    if (!createBinaryFile(fileName, recordCount)) {
        return 1;
    }

    return 0;
}
