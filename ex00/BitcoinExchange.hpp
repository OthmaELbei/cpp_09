#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <map>

class BitcoinExchange
{
    private:
        std::map<int,std::string>_data;

        int conversKey(std::string &key);
        int conversKeytext(std::string &key,std::string &value);
        double getRate(int data);
        bool isLeapYear(int year);
        int dayInmond(int year,int month);

        
        public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator= (const BitcoinExchange &other);
        void loadDatabase(const std::string &filename);
        void processInput(const std::string &filename);

};
#endif
