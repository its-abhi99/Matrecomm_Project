#include "YBConnection.h"
#include "EmployeeManagement.h"
#include <iostream>
#include <vector>
#include <string>

void addEmployeeData(EmployeeManagement& empMgmt) {
    std::string firstName, lastName, department, hireDate;
    int employeeId;

    // Get user input for employee data
    std::cout << "Enter Employee ID: ";
    std::cin >> employeeId;
    std::cin.ignore(); // To consume the newline character after integer input
    std::cout << "Enter First Name: ";
    std::getline(std::cin, firstName);
    std::cout << "Enter Last Name: ";
    std::getline(std::cin, lastName);
    std::cout << "Enter Department: ";
    std::getline(std::cin, department);
    std::cout << "Enter Hire Date (YYYY-MM-DD): ";
    std::getline(std::cin, hireDate);

    // Add employee to the database
    empMgmt.addEmployee(firstName, lastName, employeeId, department, hireDate);
}

void deleteEmployeeData(EmployeeManagement& empMgmt) {
    int employeeId;

    // Get user input for employee ID to delete
    std::cout << "Enter Employee ID to delete: ";
    std::cin >> employeeId;

    // Call the delete function from EmployeeManagement
    if (empMgmt.deleteEmployee(employeeId)) {
        std::cout << "Employee with ID " << employeeId << " deleted successfully.\n";
    } else {
        std::cout << "Error: Employee with ID " << employeeId << " not found.\n";
    }
}

void recordAttendanceData(EmployeeManagement& empMgmt) {
    int employeeId;
    std::string date, status;

    // Get user input for attendance data
    std::cout << "Enter Employee ID for attendance: ";
    std::cin >> employeeId;
    std::cin.ignore(); // To consume the newline character after integer input
    std::cout << "Enter Date (YYYY-MM-DD): ";
    std::getline(std::cin, date);
    std::cout << "Enter Attendance Status (Present/Absent): ";
    std::getline(std::cin, status);

    // Record attendance for the employee
    empMgmt.recordAttendance(employeeId, date, status);
}

void addSalaryData(EmployeeManagement& empMgmt) {
    int employeeId;
    double totalSalary;
    std::string payDate;

    // Get user input for salary data
    std::cout << "Enter Employee ID for salary details: ";
    std::cin >> employeeId;
    std::cin.ignore(); // To consume the newline character after integer input
    std::cout << "Enter Total Salary: ";
    std::cin >> totalSalary;
    std::cin.ignore(); // To consume the newline character after double input
    std::cout << "Enter Pay Date (YYYY-MM-DD): ";
    std::getline(std::cin, payDate);

    // Add salary details for the employee
    empMgmt.addSalary(employeeId, totalSalary, payDate);
}

void addSalaryComponents(EmployeeManagement& empMgmt) {
    int employeeId;
    std::string componentName;
    double componentValue;

    std::cout << "Enter Employee ID for salary components: ";
    std::cin >> employeeId;
    std::cin.ignore(); // To consume the newline character after integer input

    char addMore = 'y';
    while (addMore == 'y' || addMore == 'Y') {
        std::cout << "Enter Salary Component Name (e.g., Base Pay, HRA): ";
        std::getline(std::cin, componentName);
        std::cout << "Enter Salary Component Value: ";
        std::cin >> componentValue;
        std::cin.ignore(); // To consume the newline character after double input

        // Add salary component for the employee
        empMgmt.addSalaryComponent(employeeId, componentName, componentValue);

        // Ask if the user wants to add another component
        std::cout << "Would you like to add another salary component? (y/n): ";
        std::cin >> addMore;
        std::cin.ignore(); // To consume the newline character
    }
}

void displayEmployeeDetails(EmployeeManagement& empMgmt, int employeeId) {
    auto result = empMgmt.getEmployeeDetails(employeeId);
    while (result->next()) {
        std::cout << "Employee ID: " << result->getValue("employee_id").convert<int>() << "\n"
                  << "Name: " << result->getValue("first_name").convert<std::string>() << " "
                  << result->getValue("last_name").convert<std::string>() << "\n"
                  << "Department: " << result->getValue("department").convert<std::string>() << "\n"
                  << "Hire Date: " << result->getValue("hire_date").convert<std::string>() << "\n";
    }
}

void displayAttendanceDetails(EmployeeManagement& empMgmt, int employeeId) {
    auto attendanceResult = empMgmt.getAttendance(employeeId);
    while (attendanceResult->next()) {
        std::cout << "Date: " << attendanceResult->getValue("date").convert<std::string>() << ", Status: "
                  << attendanceResult->getValue("status").convert<std::string>() << "\n";
    }
}

void displaySalaryDetails(EmployeeManagement& empMgmt, int employeeId) {
    auto salaryResult = empMgmt.getSalaryDetails(employeeId);
    while (salaryResult->next()) {
        std::cout << "Total Salary: " << salaryResult->getValue("total_salary").convert<double>() << ", Pay Date: "
                  << salaryResult->getValue("pay_date").convert<std::string>() << "\n";
    }
}

int main() {
    try {
        // Create a connection to YugabyteDB
        auto conn = std::make_shared<YBConnection>();
        conn->connect("localhost", "5433", "yugabyte", "yugabyte", "yugabyte");

        // Instantiate EmployeeManagement
        EmployeeManagement empMgmt(conn);

        // Add some employees
        empMgmt.addEmployee("Abhishek", "Sharma", 1, "Engineering", "2024-01-15");
        empMgmt.addEmployee("Priya", "Kumar", 2, "Finance", "2023-05-20");
        empMgmt.addEmployee("Rohit", "Verma", 3, "IT", "2022-08-01");

        char choice;
        do {
            // Menu-driven interface
            std::cout << "\nEmployee Management System\n";
            std::cout << "1. Add Employee\n";
            std::cout << "2. Delete Employee\n";
            std::cout << "3. Record Attendance\n";
            std::cout << "4. Add Salary Details\n";
            std::cout << "5. Add Salary Components\n";
            std::cout << "6. Display Employee Details\n";
            std::cout << "7. Display Attendance Records\n";
            std::cout << "8. Display Salary Details\n";
            std::cout << "9. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore(); // To consume the newline character after integer input

            switch (choice) {
                case '1':
                    addEmployeeData(empMgmt);
                    break;
                case '2':
                    deleteEmployeeData(empMgmt);
                    break;
                case '3':
                    recordAttendanceData(empMgmt);
                    break;
                case '4':
                    addSalaryData(empMgmt);
                    break;
                case '5':
                    addSalaryComponents(empMgmt);
                    break;
                case '6': {
                    int employeeId;
                    std::cout << "Enter Employee ID to display details: ";
                    std::cin >> employeeId;
                    std::cin.ignore();
                    displayEmployeeDetails(empMgmt, employeeId);
                    break;
                }
                case '7': {
                    int employeeId;
                    std::cout << "Enter Employee ID to display attendance records: ";
                    std::cin >> employeeId;
                    std::cin.ignore();
                    displayAttendanceDetails(empMgmt, employeeId);
                    break;
                }
                case '8': {
                    int employeeId;
                    std::cout << "Enter Employee ID to display salary details: ";
                    std::cin >> employeeId;
                    std::cin.ignore();
                    displaySalaryDetails(empMgmt, employeeId);
                    break;
                }
                case '9':
                    std::cout << "Exiting the system.\n";
                    break;
                default:
                    std::cout << "Invalid choice! Please try again.\n";
            }

            std::cout << "Would you like to perform another action? (y/n): ";
            std::cin >> choice;
            std::cin.ignore(); // To consume the newline character after integer input

        } while (choice == 'y' || choice == 'Y');

        conn->disconnect();
    } catch (const YBError& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
