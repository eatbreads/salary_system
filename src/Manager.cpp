#include "Manager.h"

Manager::Manager(int id, const std::string& name, int level, double salary, double monthly_sales, double monthly_hours) : 
Person(id, name ,level ,salary, monthly_sales,monthly_hours) {
    setLevel(4); // 经理的等级为 4
}

double Manager::getSalary() const {
    return 18000; // 固定月薪
}

void Manager::pay() {
    // 实现付薪逻辑（可以扩展）
}
