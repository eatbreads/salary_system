#include <Saleman.h>
#include <Manager.h>
#include <SaleManager.h>
#include <Technician.h>
#include <PersonVec.h>
#include <filesystem>
#include <windows.h>
std::shared_ptr<Person> getPerson(std::shared_ptr<Person> emp)
{
    switch (emp->level)
    {
        case 1:
            return std::make_shared<Saleman>(emp->employee_id, emp->name, emp->level, emp->salary, emp->monthly_sales, emp->monthly_hours);
        case 2:
            return std::make_shared<Manager>(emp->employee_id, emp->name, emp->level, emp->salary, emp->monthly_sales, emp->monthly_hours);
        case 3:
            return std::make_shared<Technician>(emp->employee_id, emp->name, emp->level, emp->salary, emp->monthly_sales, emp->monthly_hours);
        case 4:
            return std::make_shared<Manager>(emp->employee_id, emp->name, emp->level, emp->salary, emp->monthly_sales, emp->monthly_hours);
        default:
            return nullptr; // 或者处理其他情况
    }
}


PersonVec::PersonVec(const std::string& filename)
{
    char buffer[MAX_PATH];
    std::filesystem::path m_path;
    // 使用 GetModuleFileNameA 获取当前可执行文件路径
    if (GetModuleFileNameA(NULL, buffer, MAX_PATH)) {
        // 将完整路径转换为 std::filesystem::path，并提取父目录路径
        m_path =  std::filesystem::path(buffer).parent_path();
    } else {
        // 如果失败，返回当前工作目录
        std::cerr << "Error retrieving executable path" << std::endl;
        m_path= std::filesystem::current_path();
    }
    m_filename = m_path.string()+filename;
    loadFromFile();
}

PersonVec::PersonVec(const PersonVec& other)
{
    for (const auto& pair : other.m_persons) {
        //m_persons[pair.first] = std::make_shared<Person>(*pair.second); // 使用 shared_ptr
        m_persons[pair.first] = getPerson(pair.second); // 间接创建
    }
    m_filename = other.m_filename;
}

PersonVec::~PersonVec()
{
    saveToFile();
}

void PersonVec::insert(std::shared_ptr<Person> emp)
{
    auto empptr = getPerson(emp);

    if(m_persons.find(empptr->name)!=m_persons.end())
    {
        std::cout << "Employee " << empptr->name << " already exists." << std::endl;
        return;
    }
    Person::count++;
    m_persons[empptr->name] = empptr;
}

void PersonVec::remove(const std::string& name)
{
    auto it = m_persons.find(name);
    if(it != m_persons.end())
    {
        m_persons.erase(it);
        std::cout << "Employee " << name << " removed successfully." << std::endl;
    }
    else
    {
        std::cout << "Employee " << name << " not found." << std::endl;
    }
}
void PersonVec::update(std::shared_ptr<Person> emp)
{
    auto it = m_persons.find(emp->name);
    if(it!= m_persons.end())
    {
        it->second = emp;
        std::cout << "Employee " << emp->name << " updated successfully." << std::endl;
    }
    else
    {
        std::cout << "Employee " << emp->name << " not found." << std::endl;
    }
}
void PersonVec::display() const {
    // 创建一个 vector 来存储员工指针
    std::vector<std::shared_ptr<Person>> sortedPersons;

    // 将所有员工放入 vector 中
    for (const auto& pair : m_persons) {
        sortedPersons.push_back(pair.second);
    }

    // 根据员工的职位等级 level 进行排序，职位级别较高的排在前面
    std::sort(sortedPersons.begin(), sortedPersons.end(), [](const std::shared_ptr<Person>& a, const std::shared_ptr<Person>& b) {
        return a->getLevel() > b->getLevel(); // 降序排序，级别大的排在前面
    });

    // 遍历 vector，调用 display() 方法
    for (const auto& person : sortedPersons) {
        person->display();
    }
}

std::shared_ptr<Person> PersonVec::find(const std::string& id)const
{
    auto it = m_persons.find(id);
    if(it!= m_persons.end())
    {
        return it->second;
    }
    std::cout << "❌没找到员工" <<std::endl;
    return nullptr;
}

// 以下为重载的操作符
PersonVec& PersonVec::operator=(const PersonVec& other)
{
    for (const auto& pair : other.m_persons) {
        //m_persons[pair.first] = std::make_shared<Person>(*pair.second); // 使用 shared_ptr
        m_persons[pair.first] = getPerson(pair.second); // 转换为对应的子类并使用 shared_ptr
    }
    m_filename = other.m_filename;
    return *this;
}

void PersonVec::loadFromFile()
{
    io::CSVReader<6> in(m_filename);
    in.read_header(io::ignore_extra_column, "员工编号", "姓名", "级别", "薪水", "销售额", "工作时间");

    int id;
    std::string name;
    int level;
    double salary;
    double sales;
    double workHours;

    while (in.read_row(id, name, level, salary, sales, workHours)) {//这里也抛出异常了
        //我严重怀疑是下面这一条编译过不去,不存在这种构造,而且抽象基类不可以直接new
        //即使不是抽象基类,好像也不支持这样间接构造吧
        //m_persons[name]=(std::make_shared<Person>(id, name, level, salary, sales, workHours));
        
        std::shared_ptr<Person> emp;
        // 根据等级创建不同的类
        if (level == 1) {
            emp = std::make_shared<Saleman>(id, name,level, salary, sales, workHours);
        } else if (level == 2) {
            emp = std::make_shared<SaleManager>(id, name, level,salary, sales, workHours);
        } else if (level == 3) {
            // 处理其他等级或使用默认员工类
            emp = std::make_shared<Technician>(id, name, level, salary, sales, workHours); // 这需要确保 Person 不是抽象的
        }else{
            emp = std::make_shared<Manager>(id, name, level, salary, sales, workHours);
        }
        //根据当前的id来更新person::count的值
        if(emp->employee_id > Person::count)
        {
            Person::count = emp->employee_id;
            //std::cout << "更新了person::count的值:" <<Person::count<< std::endl;
        }
        m_persons[name] = emp; // 假设员工姓名是唯一的
    }
}

void PersonVec::saveToFile() const
{
    std::ofstream outFile(m_filename); // 以追加模式打开文件
    outFile << "员工编号,姓名,级别,薪水,销售额,工作时间\n"; 
    std::map<int,std::shared_ptr<Person>> m_persons_back;
    for(const auto& person : m_persons)
    {
        m_persons_back[person.second->employee_id] = person.second; // 备份person::count的值
    }
    for (const auto& emp : m_persons_back) {
        outFile << emp.second->employee_id << ',' << emp.second->name << ',' 
                  << emp.second->level << ',' << emp.second->salary << ','
                  << emp.second->monthly_sales << ',' << emp.second->monthly_hours << '\n';
    }
    outFile.close();
}
void PersonVec::displayNotPayed() const
{
    for(const auto& person : m_persons)
    {
        if(person.second->salary <= 0)
        {
            person.second->display();
        }
    }
}