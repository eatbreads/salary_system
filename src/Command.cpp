#include "Command.h"

Command::Command() {
    // 注册默认命令
    registerCommand("help", [this]() { showHelp(); });
    registerCommand("1", [this]() { enterEmployeeData(); });
    registerCommand("2", [this]() { addEmployee(); });
    registerCommand("3", [this]() { removeEmployee(); });
    registerCommand("4", [this]() { paySalary(); });
    registerCommand("5", [this]() { displaySalaryTable(); });
    registerCommand("6", [this]() { clearSalary(); }); // 注册 'quit' 作为退出命令
}

void Command::registerCommand(const std::string& command, const std::function<void()>& func) {
    commands[command] = func; // 注册命令及其对应的函数
}

void Command::listen() {
    showHelp();
    std::string input;
    while (true) {
        std::cout << "请输入命令: ";
        
        // std::getline(std::cin, input);
        std::cin >> input;
        // 将输入转换为小写，以便于匹配
        std::string command = input;
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command == "退出" || command == "0") 
        {
            break; // 退出循环
        }// 解析命令并执行
        if (commands.count(command)) 
        {
            commands[command](); // 执行对应的函数
            std::cout << std::endl << std::endl;
        }         
        else {
            std::cout <<std::endl<< "未知命令，请重新输入或输入 '帮助' 查看可用命令。\n";
            std::cout << std::endl;
        }
    }
}

void Command::showHelp() {
    std::cout <<std::endl<<std::endl<< "-----------打印帮助文档------------"<< std::endl;
    std::cout << "可用命令选项：" << std::endl;
    std::cout << "1. 录入职工资料" << std::endl;
    std::cout << "2. 增加职工" << std::endl;
    std::cout << "3. 删除职工" << std::endl;
    std::cout << "4. 月薪发放" << std::endl;
    std::cout << "5. 显示工资表" << std::endl;
    std::cout << "0. 退出系统" << std::endl;
}

void Command::enterEmployeeData() {
    // 录入员工信息的逻辑
    std::cout << "录入职工资料...\n";
    int id, level;
    std::string name;
    double salary, sales, workHours;

    std::cout << "请输入员工编号: ";
    std::cin >> id;
    std::cout << "请输入姓名: ";
    std::cin >> name;
    std::cout << "请输入级别: ";
    std::cin >> level;
    // std::cout << "请输入薪水: ";
    // std::cin >> salary;
    std::cout << "请输入销售额: ";
    std::cin >> sales;
    std::cout << "请输入工作时间: ";
    std::cin >> workHours;

    std::shared_ptr<Person> emp;
    if (level == 1) {
        emp = std::make_shared<Saleman>(id, name, level, 0, sales, workHours);
    } else if (level == 2) {
        emp = std::make_shared<SaleManager>(id, name, level, 0, sales, workHours);
    } else if (level == 3) {
        emp = std::make_shared<Technician>(id, name, level, 0, sales, workHours);
    } else {
        emp = std::make_shared<Manager>(id, name, level, 0, sales, workHours);
    }

    m_personVec.insert(emp);
}

void Command::addEmployee() {
    // 调用录入职工资料
    enterEmployeeData();
    std::cout << "-----------增加职工-----------\n";
}

void Command::removeEmployee() {
    std::cout << "请输入要删除的员工姓名: ";
    std::string name;
    std::cin >> name;
    m_personVec.remove(name);
}

void Command::paySalary() {
    std::cout << "------------发放月薪------------\n";
    // 可以在这里实现发放工资的具体逻辑
    std::cout << "请输入需要发放的员工名字: ";
    std::string name;
    std::cin >> name;
    auto it = m_personVec.find(name);
    //如果这个智能指针不为空
    if(it.get()!=nullptr)
    {
        it->pay();
    }
    displaySalaryTable();

}

void Command::displaySalaryTable() {
    std::cout << "-------------显示工资表--------------\n";
    m_personVec.display();
}

void Command::clearSalary()
{
    std::cout << "-------------员工的月--------------\n";
    std::cout << "请输入要撤销的员工薪资:";
    std::string name;
    std::cin >> name;
    auto it = m_personVec.find(name);
    if(it.get()!=nullptr)
    {
        it->clearSalary();
    }
    displaySalaryTable();
}
    