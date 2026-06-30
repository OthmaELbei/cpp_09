#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <map>

int  conversKey(std::string &key)
{
    std::string resolt = "";

    for (size_t i = 0; i < key.length(); i++)
    {
        if (key[i] != '-')
            resolt += key[i];
    }
    return atoi(resolt.c_str());
}
int conversKeytext(std::string &key, std::string &value)
{
    std::stringstream ss(key);
    std::string year;
    std::string month;
    std::string day;
    std::getline(ss, year, '-');
    std::getline(ss, month, '-');
    std::getline(ss, day, '-');
    int yurs = atoi(year.c_str());
    int months = atoi(month.c_str());
    int days = atoi(day.c_str());
    int flags = 0;

    if (yurs < 2009)
        std::cout << "Error: bad input => " << key << std::endl;
    else if (months < 1 || months > 12)
        std::cout << "Error: bad input => " << key << std::endl;
    else if (days < 1 || days > 31)
        std::cout << "Error: bad input => " << key << std::endl;
    else
    {
        flags = 1;
    }

    float values = atof(value.c_str());
    if (flags && values < 0)
        std::cout << "Error: not a positive number." << std::endl, flags = 0;
    else if (flags && values > 1000)
        std::cout << "Error: too large a number." << std::endl, flags = 0;

    return flags;
}
double getRate(std::map<int, std::string> &data, int date)
{
    std::map<int, std::string>::const_iterator it;
    it = data.lower_bound(date);

    if (it != data.end() && it->first == date)
        return atof(it->second.c_str());

    if (it == data.begin())
        return 0;

    --it;
    return atof(it->second.c_str());
}
int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    std::ifstream file("data.csv");
    std::ifstream files(av[1]);

    if (!files)
    {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line);

    std::map<int, std::string> data;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string key;
        std::string value;

        std::getline(ss, key, ',');
        std::getline(ss, value, ',');
        int keyConfige = conversKey(key);

        data[keyConfige] = value;
    }

    std::string lents;
    std::getline(files, lents);

    int flags = 0;
    while (std::getline(files, lents))
    {
        if (lents.empty())
            continue;

        std::stringstream ss(lents);
        std::string key;
        std::string value;

        std::getline(ss, key, '|');
        std::getline(ss, value, '|');

        flags = conversKeytext(key, value);

        if (flags)
        {
            int dateKey = conversKey(key);
            double rate = getRate(data, dateKey);
            float values = atof(value.c_str());
            double result = values * rate;

            std::stringstream cleanKey(key);
            std::string dateClean;
            cleanKey >> dateClean;

            std::cout << dateClean << " => " << values
                      << " = " << result << std::endl;
        }
    }

    file.close();
    files.close();

    return 0;
}

