#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <map>
#include <csv.h>
#include <memory>

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
    static int getCount(); // 获取当前员工数
};


class PersonVec
{
    //使用map来存储,要求key为int,且逆序存储
    std::map<std::string,std::shared_ptr<Person>> m_persons;
    std::string m_filename;
    void loadFromFile();
    void saveToFile() const;
public:
    PersonVec(const std::string& filename="E:/vscodecodecodecoe/CPP/salary_system/person.csv");
    //拷贝构造和析构
    PersonVec(const PersonVec& other);
    ~PersonVec();

    void insert(std::shared_ptr<Person> emp);
    void remove(const std::string& name);
    void update(std::shared_ptr<Person> emp);
    void display() const;
    
    std::shared_ptr<Person> find(const std::string& name) const;
    
    // 以下为重载的操作符
    PersonVec& operator=(const PersonVec& other);

    
};

#endif
