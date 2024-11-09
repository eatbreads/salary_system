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
const std::string reset = "\033[0m";
const std::string bold = "\033[1m";
const std::string cyan = "\033[36m";
const std::string yellow = "\033[33m";
const std::string green = "\033[32m";
const std::string magenta = "\033[35m";
void Person::display() {
    std::string levelEmoji;
    if (level == 4) {
        levelEmoji = "👑 经理";
    } else if (level == 3) {
        levelEmoji = "👔 销售经理";
    } else if (level == 2) {
        levelEmoji = "💻 技术员";
    } else if (level == 1) {
        levelEmoji = "🛒 销售员";
    } else {
        levelEmoji = "❓ 未知职位";
    }

    std::cout << cyan << "📇 员工信息: " 
              << yellow << "🆔 " << employee_id << reset << ", "
              << green << "👤 " << name << reset << ", "
              << magenta << levelEmoji << reset << ", "
              << cyan << "💰 " << salary << reset << std::endl;
}


