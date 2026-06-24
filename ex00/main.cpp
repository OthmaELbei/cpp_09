#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange btc;
    btc.loadDatabase("data.csv");   // قاعدة البيانات الموجودة مع المشروع
    btc.processInput(av[1]);        // ملف الإدخال من المستخدم

    return 0;
}