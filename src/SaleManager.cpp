#include "SaleManager.h"

SaleManager::SaleManager(int id, const std::string& name, int level, double salary, double monthly_sales, double monthly_hours) 
:Person(id,name,level, salary, monthly_sales, monthly_hours),//菱形继承要优先保证基类的构造函数先被调用
Manager(id,name,level, salary, monthly_sales, monthly_hours),
Saleman(id,name,level, salary, monthly_sales, monthly_hours)
{
    setLevel(2); // 销售经理的等级为 2
}

double SaleManager::getSalary() const {
    return Manager::getSalary() + (monthly_sales * 0.02); // 固定薪水加销售提成
}

void SaleManager::pay() {
    // 实现付薪逻辑（可以扩展）
}
