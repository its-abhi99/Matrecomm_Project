// EmployeeManagement.cpp

#include "EmployeeManagement.h"
#include "YBError.h"
#include <iostream>

EmployeeManagement::EmployeeManagement(std::shared_ptr<YBConnection> conn) : _connection(std::move(conn)) {}

void EmployeeManagement::addEmployee(const std::string& firstName, const std::string& lastName, int roleId, const std::string& department, const std::string& dateOfJoining) {
    YBQuery query(_connection);
    query.executeQuery("INSERT INTO Employees (first_name, last_name, role_id, department, date_of_joining) VALUES ('" 
                        + firstName + "', '" + lastName + "', " + std::to_string(roleId) + ", '" + department + "', '" + dateOfJoining + "');");
    std::cout << "Employee added successfully.\n";
}

void EmployeeManagement::recordAttendance(int employeeId, const std::string& date, const std::string& status) {
    YBQuery query(_connection);
    query.executeQuery("INSERT INTO Attendance (employee_id, date, status) VALUES (" + std::to_string(employeeId) + ", '" + date + "', '" + status + "');");
    std::cout << "Attendance recorded successfully.\n";
}

void EmployeeManagement::addSalary(int employeeId, double totalSalary, const std::string& payDate) {
    YBQuery query(_connection);
    query.executeQuery("INSERT INTO Salaries (employee_id, total_salary, pay_date) VALUES (" 
                        + std::to_string(employeeId) + ", " + std::to_string(totalSalary) + ", '" + payDate + "');");
    std::cout << "Salary added successfully.\n";
}

void EmployeeManagement::addSalaryComponent(int salaryId, const std::string& componentName, double amount) {
    YBQuery query(_connection);
    query.executeQuery("INSERT INTO SalaryComponents (salary_id, component_name, amount) VALUES (" 
                        + std::to_string(salaryId) + ", '" + componentName + "', " + std::to_string(amount) + ");");
    std::cout << "Salary component added successfully.\n";
}

std::shared_ptr<YBResult> EmployeeManagement::getEmployeeDetails(int employeeId) {
    YBQuery query(_connection);
    return query.executeQuery("SELECT * FROM Employees WHERE employee_id = " + std::to_string(employeeId) + ";");
}

std::shared_ptr<YBResult> EmployeeManagement::getAttendance(int employeeId) {
    YBQuery query(_connection);
    return query.executeQuery("SELECT * FROM Attendance WHERE employee_id = " + std::to_string(employeeId) + ";");
}

std::shared_ptr<YBResult> EmployeeManagement::getSalaryDetails(int employeeId) {
    YBQuery query(_connection);
    return query.executeQuery("SELECT * FROM Salaries WHERE employee_id = " + std::to_string(employeeId) + ";");
}

bool EmployeeManagement::deleteEmployee(int employeeId) {
    try {
        // Delete employee-related records first if needed (e.g., attendance, salary components)
        YBQuery query(_connection);
        query.executeQuery("DELETE FROM SalaryComponents WHERE salary_id IN (SELECT salary_id FROM Salaries WHERE employee_id = " + std::to_string(employeeId) + ");");
        query.executeQuery("DELETE FROM Salaries WHERE employee_id = " + std::to_string(employeeId) + ";");
        query.executeQuery("DELETE FROM Attendance WHERE employee_id = " + std::to_string(employeeId) + ";");
        
        // Now delete the employee from the Employees table
        query.executeQuery("DELETE FROM Employees WHERE employee_id = " + std::to_string(employeeId) + ";");
        std::cout << "Employee deleted successfully.\n";
        return true;
    } catch (const YBError& e) {
        std::cerr << "Error while deleting employee: " << e.what() << std::endl;
        return false;
    }
}
