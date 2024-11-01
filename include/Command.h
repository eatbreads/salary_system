#pragma once
#include <string>
#include <functional>
#include <map>
#include <iostream>
#include <algorithm>
#include <Person.h>
#include <Manager.h>
#include <SaleManager.h>
#include <Technician.h>
class Command {
private:
    std::map<std::string, std::function<void()>> commands;
    PersonVec m_personVec;
    void showHelp();
    void enterEmployeeData();
    void addEmployee();
    void removeEmployee();
    void paySalary();
    void displaySalaryTable();
    
public:
    Command();
    void registerCommand(const std::string& command, const std::function<void()>& func);
    void listen();
};
