#ifndef TECHNICIAN_H
#define TECHNICIAN_H

#include "Person.h"

class Technician : public Person {
private:
    

public:
    Technician(int id, const std::string& name, int level, double salary, double monthly_sales, double monthly_hours);
    double getSalary() const override; // 重写返回工资
    void pay() override; // 重写付薪函数
};

#endif
