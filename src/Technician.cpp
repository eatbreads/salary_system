#include "Technician.h"

Technician::Technician(int id, const std::string& name, int level, double salary, double monthly_sales, double monthly_hours) 
: Person(id, name ,level ,salary, monthly_sales,monthly_hours) 
{
    setLevel(3); // 技术人员的等级为 3
}

double Technician::getSalary() const {
    return monthly_hours * 100; // 按小时计算薪水
}

void Technician::pay() {
    std::cout << "工作时长为:" << monthly_hours << std::endl;
    std::cout << "Technician " << getName() << " has been paid $" << getSalary()<< std::endl;
    this->salary = getSalary();
}
