#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <map>
#include <csv.h>
#include <memory>
#include <iostream>
class Person {
protected:
    int employee_id{};
    std::string name{};
    int level{};
    double salary{};
    double monthly_sales{}; // 月度销售额
    double monthly_hours{}; // 月工作时间
    

public:
    static int count; // 静态数据成员，记录当前员工数
    friend class PersonVec;
    friend std::shared_ptr<Person> getPerson(std::shared_ptr<Person> emp);
    Person(int id, const std::string& name, int level, double salary, double monthly_sales, double monthly_hours);

    virtual double getSalary() const = 0; // 纯虚函数
    virtual void pay() = 0; // 纯虚函数
    void setLevel(int level);
    int getEmployeeID() const;
    std::string getName() const;
    int getLevel() const;
    void display();
    void clearSalary();
    static int getCount(); // 获取当前员工数
};



#endif
