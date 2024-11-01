#ifndef SALEMANAGER_H
#define SALEMANAGER_H

#include "Manager.h"
#include "Saleman.h"

class SaleManager : public Manager, public Saleman {
public:
    SaleManager(int id, const std::string& name, int level, double salary, double monthly_sales, double monthly_hours);
    double getSalary() const override; // 重写返回工资
    void pay() override; // 重写付薪函数
};

#endif
