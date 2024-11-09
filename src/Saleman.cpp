#include "Saleman.h"
#include <iostream>
Saleman::Saleman(int id, const std::string& name, int level, double salary, double monthly_sales, double monthly_hours) : 
Person(id, name ,level ,salary, monthly_sales,monthly_hours) {
    setLevel(1); // 推销员的等级为 1
}

double Saleman::getSalary() const {
    return monthly_sales * 0.04; // 按销售额的 4% 提成
}

void Saleman::pay() {
    // 实现付薪逻辑（可以扩展）
    std::cout << "✅Paying " << name << " a salary of $" << getSalary() << std::endl;
    this->salary = getSalary();
}
