#include "Command.h"

Command::Command() {
    // 注册默认命令
    registerCommand("help", [this]() { showHelp(); });
    registerCommand("1", [this]() { enterEmployeeData(); });
    registerCommand("2", [this]() { addEmployee(); });
    registerCommand("3", [this]() { removeEmployee(); });
    registerCommand("4", [this]() { paySalary(); });
    registerCommand("5", [this]() { displaySalaryTable(); });
    registerCommand("6", [this]() { displaySalaryNeYetPay(); }); // 注册 'display' 作为显示工资统计命令
    registerCommand("7", [this]() { clearSalary(); }); // 注册 'quit' 作为退出命令
}

void Command::registerCommand(const std::string& command, const std::function<void()>& func) {
    commands[command] = func; // 注册命令及其对应的函数
}

// 控制台颜色代码
const std::string reset = "\033[0m";
const std::string bold = "\033[1m";
const std::string cyan = "\033[36m";
const std::string yellow = "\033[33m";
const std::string green = "\033[32m";
const std::string red = "\033[31m";
const std::string magenta = "\033[35m";

void Command::showHelp() {
    std::cout << cyan << bold << "\n\n✨✨✨ 公司薪酬管理系统 ✨✨✨" << reset << std::endl;
    std::cout << yellow << "------------------------- 可用命令选项 -------------------------" << reset << std::endl;
    std::cout << green << "1️⃣ 录入职工资料" << reset << std::endl;
    std::cout << green << "2️⃣ 增加职工" << reset << std::endl;
    std::cout << green << "3️⃣ 删除职工" << reset << std::endl;
    std::cout << green << "4️⃣ 月薪发放" << reset << std::endl;
    std::cout << green << "5️⃣ 显示全部工资表" << reset << std::endl;
    std::cout << green << "6️⃣ 显示待处理的工资名单" << reset << std::endl;
    std::cout << green << "7️⃣ 撤销某人的月薪发放" << reset << std::endl;
    std::cout << red << "0️⃣ 退出系统" << reset << std::endl;
    std::cout << yellow << "--------------------------------------------------------------" << reset << std::endl;
}

void Command::listen() {
     showHelp();
    std::string input;
    while (true) {
        // showHelp();
        std::cout << magenta << bold << "\n👉 请输入命令(help查看帮助): " << reset;
        
        std::cin >> input;
        std::string command = input;
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command == "退出" || command == "0") 
        {
            std::cout << red << "🔴 退出系统，感谢使用！" << reset << std::endl;
            break;
        }
        if (commands.count(command)) {
            commands[command]();
            // std::cout << std::endl << std::endl;
        } else {
            std::cout << red << "\n❌ 未知命令，请重新输入或输入 '帮助' 查看可用命令。\n" << reset;
        }
    }
}

void Command::enterEmployeeData() {
    
    int level = 4;  // 从经理开始录入
    std::string name;
    double sales = 0.0, workHours = 0.0;
    std::shared_ptr<Person> emp;

    std::cout << bold << "\n📋 开始录入职工资料 (输入 '@' 跳到下一个职位等级)..." << reset << std::endl;

    while (level >= 1) {
        int id = Person::count + 1;
        if (level == 4) {  // 经理
            std::cout << "👑 经理 - 请输入姓名 (输入 '@' 进入下一职位): ";
            std::cin >> name;
            if (name == "@") {
                level = 3;
                continue;
            }
            emp = std::make_shared<Manager>(id, name, level, 0, 0, 0);
        } 
        else if (level == 3) {  // 销售经理
            std::cout << "👔 销售经理 - 请输入姓名 (输入 '@' 进入下一职位): ";
            std::cin >> name;
            if (name == "@") {
                level = 2;
                continue;
            }
            std::cout << "🛒请输入销售额: ";
            std::cin >> sales;
            emp = std::make_shared<SaleManager>(id, name, level, 0, sales, workHours);
        } 
        else if (level == 2) {  // 技术员
            std::cout << "💻 技术员 - 请输入姓名 (输入 '@' 进入下一职位): ";
            std::cin >> name;
            if (name == "@") {
                level = 1;
                continue;
            }
            std::cout << "⌛请输入工作时间: ";
            std::cin >> workHours;
            emp = std::make_shared<Technician>(id, name, level, 0, 0, workHours);
        } 
        else if (level == 1) {  // 推销员
            std::cout << "🛒 推销员 - 请输入姓名 (输入 '@' 完成录入): ";
            std::cin >> name;
            if (name == "@") break;
            std::cout << "📈请输入销售额: ";
            std::cin >> sales;
            emp = std::make_shared<Saleman>(id, name, level, 0, sales, workHours);
        }

        // 将创建的员工对象插入到员工列表中
        m_personVec.insert(emp);
        std::cout << green << "✅ 职工资料录入完成！" << reset << std::endl;
    }

    std::cout << bold << cyan << "📋 所有职工资料录入完成。" << reset << std::endl;
}


void Command::addEmployee() {
    std::cout << bold << green << "\n📈 增加职工..." << reset << std::endl;
    enterEmployeeData();
}

void Command::removeEmployee() {
    std::cout << bold << red << "\n🗑️ 请输入要删除的员工姓名: " << reset;
    std::string name;
    std::cin >> name;
    m_personVec.remove(name);
    std::cout << green << "✅ 职工 " << name << " 删除成功！" << reset << std::endl;
}

void Command::paySalary() {
    std::cout << bold << "\n💸 发放月薪..." << reset << std::endl;
    std::cout << "💸请输入需要发放的员工名字: ";
    std::string name;
    std::cin >> name;
    auto it = m_personVec.find(name);
    if (it.get() != nullptr) {
        it->pay();
    }
    displaySalaryTable();
}

void Command::displaySalaryTable() {
    std::cout << bold << "\n📊 显示全部工资表..." << reset << std::endl;
    m_personVec.display();
}

void Command::clearSalary() {
    std::cout << bold << "\n🔄 撤销员工的月薪发放..." << reset << std::endl;
    std::cout << "请输入要撤销的员工薪资: ";
    std::string name;
    std::cin >> name;
    auto it = m_personVec.find(name);
    if (it.get() != nullptr) {
        it->clearSalary();
    }
    displaySalaryTable();
}

void Command::displaySalaryNeYetPay() {
    std::cout << bold << "\n📋 显示待处理工资表..." << reset << std::endl;
    m_personVec.displayNotPayed();
}