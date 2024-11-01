// #include "Command.h"
//#include "csv.h" // 引入 CSV 头文件
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <io.h>
#include <fcntl.h>
int main() {
    std::string test="金额";
    std::cout << test << std::endl;
    std::cin >> test;
    std::cout << test << std::endl;
    // _setmode(_fileno(stdout), _O_U8TEXT);
    // _setmode(_fileno(stdin), _O_U8TEXT);
    // Command command;
    // command.listen(); // 启动命令监听
    // std::cout << "Command" << std::endl;
    return 0;
}