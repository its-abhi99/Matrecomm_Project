// EmployeeManagement.h

#pragma once

#include <string>
#include <memory>
#include "YBConnection.h"
#include "YBQuery.h"
#include "YBResult.h"

class EmployeeManagement {
public:
    EmployeeManagement(std::shared_ptr<YBConnection> conn);
    
    void addEmployee(const std::string& firstName, const std::string& lastName, int roleId, const std::string& department, const std::string& dateOfJoining);
    void recordAttendance(int employeeId, const std::string& date, const std::string& status);
    void addSalary(int employeeId, double totalSalary, const std::string& payDate);
    void addSalaryComponent(int salaryId, const std::string& componentName, double amount);
    
    std::shared_ptr<YBResult> getEmployeeDetails(int employeeId);
    std::shared_ptr<YBResult> getAttendance(int employeeId);
    std::shared_ptr<YBResult> getSalaryDetails(int employeeId);

    bool deleteEmployee(int employeeId);  // Declare the deleteEmployee method

private:
    std::shared_ptr<YBConnection> _connection;
};
