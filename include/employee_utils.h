/* employee_utils.h */
#ifndef EMPLOYEE_UTILS_H
#define EMPLOYEE_UTILS_H

#include "employee.h"
#include <stdexcept>
#include <cstring>
#include <cctype>

inline void validateEmployee(const employee& emp) {
    if (emp.num <= 0) {
        throw std::invalid_argument("Employee number must be positive");
    }

    if (emp.hours < 0.0 || emp.hours > 168.0) {
        throw std::invalid_argument("Working hours must be in range [0, 168]");
    }

    bool nullTerminated = false;
    for (int i = 0; i < 10; ++i) {
        if (emp.name[i] == '\0') {
            nullTerminated = true;
            break;
        }
    }
    if (!nullTerminated) {
        throw std::invalid_argument("Name is not null-terminated");
    }

    if (emp.name[0] == '\0') {
        throw std::invalid_argument("Name must not be empty");
    }

    for (int i = 0; i < 10 && emp.name[i] != '\0'; ++i) {
        if (!isprint(static_cast<unsigned char>(emp.name[i]))) {
            throw std::invalid_argument("Name contains non-printable character");
        }
    }
}

#endif // EMPLOYEE_UTILS_H
