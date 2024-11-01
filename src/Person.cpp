#include "Person.h"
#include <iostream>
#include <fstream>
// 静态成员初始化
int Person::count = 2001;


Person::Person(int id, const std::string& name, int level, double salary, double monthly_sales, double monthly_hours)
{
    this->employee_id = id;
    this->name = name;
    this->level = level;
    this->salary = salary;
    this->monthly_sales = monthly_sales;
    this->monthly_hours = monthly_hours;
}
void Person::setLevel(int level) {
    this->level = level;
}

int Person::getEmployeeID() const {
    return employee_id;
}

std::string Person::getName() const {
    return name;
}

int Person::getLevel() const {
    return level;
}

int Person::getCount() {
    return count - 1; // 返回当前员工数
}
void Person::clearSalary()
{
    salary = 0;
}
 void Person::display()
 {
    std::cout << "Employee ID: " << employee_id << ", Name: " << name << ", Level: " << level 
              << ", Salary: " << salary << std::endl;
 }

