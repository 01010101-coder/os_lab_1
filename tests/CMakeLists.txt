add_executable(tests_employee test_employee.cpp)
target_include_directories(tests_employee PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(tests_employee gtest_main)

add_test(NAME EmployeeValidationTests COMMAND tests_employee)
