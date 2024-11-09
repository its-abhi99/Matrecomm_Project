// main_test.cpp

#include <iostream>
#include "YBConnection.h"
#include "YBQuery.h"
#include "YBResult.h"
#include "EmployeeManagement.h"

int main() {
    auto conn = std::make_shared<YBConnection>();
    conn->connect("localhost", "5433", "yugabyte", "yugabyte", "yugabyte");
    EmployeeManagement empMgmt(conn);

    // Add a new employee to test the deletion
    std::string firstName, lastName, department, dateOfJoining;
    int roleId;
    std::cout << "Enter first name: ";
    std::cin >> firstName;
    std::cout << "Enter last name: ";
    std::cin >> lastName;
    std::cout << "Enter role ID: ";
    std::cin >> roleId;
    std::cout << "Enter department: ";
    std::cin >> department;
    std::cout << "Enter date of joining (YYYY-MM-DD): ";
    std::cin >> dateOfJoining;

    empMgmt.addEmployee(firstName, lastName, roleId, department, dateOfJoining);

    // Delete the employee with ID 1 (or the employee added in the above code)
    int employeeIdToDelete = 1;  // Or use the ID of the employee you added
    bool deleteResult = empMgmt.deleteEmployee(employeeIdToDelete);
    
    if (deleteResult) {
        std::cout << "Employee deleted successfully.\n";
    } else {
        std::cout << "Failed to delete employee.\n";
    }

    conn->disconnect();
    return 0;
}
