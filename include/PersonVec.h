#pragma once
#include <string>
#include <vector>
#include <map>
#include <csv.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <Person.h>
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
    //展示还未发放工资的名单
    void displayNotPayed() const;
    
    std::shared_ptr<Person> find(const std::string& name) const;
    
    // 以下为重载的操作符
    PersonVec& operator=(const PersonVec& other);

    
};
