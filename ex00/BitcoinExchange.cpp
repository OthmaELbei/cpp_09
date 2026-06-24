
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    _data = other._data;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        _data = other._data;
    return *this;
}
int BitcoinExchange::conversKey(std::string &key)
{
    std::string resolt = "";

    for (size_t i = 0; i < key.length(); i++)
    {
        if (key[i] != '-')
            resolt += key[i];
    }
    return atoi(resolt.c_str());
}
int handelMonth(int y, int m)
{
    if (m < 1 || m > 12)
        return 0;

    if (m == 2)
    {
        bool leap = (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
        return leap ? 29 : 28;
    }

    if (m == 4 || m == 6 || m == 9 || m == 11)
        return 30;

    return 31;
}
int hendelDate(int yurs ,int months, int days ,std::string key)
{
      int flags = 0;
int hendldays = handelMonth(yurs,months);
   if (yurs < 2009)
        std::cout << "Error: bad input => " << key << std::endl;
    else if (months < 1 || months > 12)
        std::cout << "Error: bad input => " << key << std::endl;
    else if (days < 1 || days > hendldays)
        std::cout << "Error: bad input => " << key << std::endl;
    else
    {
        flags = 1;
    }
    return flags;
}
int BitcoinExchange::conversKeytext(std::string &key, std::string &value)
{
    std::string tremmkey = "";
     for (size_t i = 0; i < key.length(); i++)
    {
        if (key[i] != ' ')
            tremmkey += key[i];
    }
    std::string tremmvalue = "";
    for (size_t i = 0; i < value.length(); i++)
    {
        if (value[i] != ' ')
            tremmvalue += value[i];
    }
    if(tremmvalue.empty())
    {
        std::cout <<"Error: bad input => "  << tremmkey << std::endl;
        return  0;
    }
    std::stringstream ss(tremmkey);
    std::string year;
    std::string month;
    std::string day;
    std::getline(ss, year, '-');
    std::getline(ss, month, '-');
    std::getline(ss, day, '-');

    if(year.empty() || month.empty() || day.empty()){

        std::cout << "date is not valid " << std::endl;
        return 0;
    }
    
    int yurs = atoi(year.c_str());
    int months = atoi(month.c_str());
    int days = atoi(day.c_str());
  
 int flags =hendelDate(yurs,months,days,tremmkey);

    float values = atof(tremmvalue.c_str());
    if (flags && values < 0)
        std::cout << "Error: not a positive number." << std::endl, flags = 0;
    else if (flags && values > 1000)
        std::cout << "Error: too large a number." << std::endl, flags = 0;
if(flags)
{
    key = tremmkey;
    value = tremmvalue;
}
    return flags;
}
double BitcoinExchange::getRate(int date)
{
   std::map<int, std::string>::const_iterator it;
    it = _data.lower_bound(date);

    if (it != _data.end() && it->first == date)
        return atof(it->second.c_str());

    if (it == _data.begin())
        return 0;

    --it;
    return atof(it->second.c_str());
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
    std::ifstream file(filename.c_str());

    if (!file)
    {
        std::cout << "Error: could not open database file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string key;
        std::string value;

        std::getline(ss, key, ',');
        std::getline(ss, value, ',');
        int keyConfige = conversKey(key);

        _data[keyConfige] = value;
    }
    file.close();
}

void BitcoinExchange::processInput(const std::string &filename)
{
    std::ifstream files(filename.c_str());

    if (!files)
    {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }

    std::string lents;
    std::getline(files, lents); 

    while (std::getline(files, lents))
    {
        if (lents.empty())
            continue;

        std::stringstream ss(lents);
        std::string key;
        std::string value;

        std::getline(ss, key, '|');
        std::getline(ss, value, '|');

        int flags = conversKeytext(key, value);

        if (flags)
        {
            int dateKey = conversKey(key);
            double rate = getRate(dateKey);
            float values = atof(value.c_str());
            double result = values * rate;

            std::stringstream cleanKey(key);
            std::string dateClean;
            cleanKey >> dateClean;

            std::cout << dateClean << " => " << values
                      << " = " << result << std::endl;
        }
    }
    files.close();
}