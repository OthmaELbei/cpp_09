#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <map>

int conversKey(std::string &key)
{
    std::string resolt = "";
    for (size_t i = 0; i < key.length(); i++)
    {
        if (key[i] != '-')
            resolt += key[i];
    }
    return atoi(resolt.c_str());
}
int conversKeytext(std::string &key)
{
    std::string resolt = "";
    for (size_t i = 0; i < key.length(); i++)
    {
        if (key[i] != '-')
            resolt += key[i];
    }
    return atoi(resolt.c_str());
}

int main(int ac, char **av)
{
    std::ifstream file("data.csv");
    
    std::ifstream files(av[1]);

    std::string lents ;
      std::getline(files, lents);

    std::map<int, std::string> data;
    while (std::getline(files, lents))
    {
        std::stringstream ss(lents);
        std::string key;
        std::string value;

        std::getline(ss, key, '|');
        std::getline(ss, value, '|');
        int keyConfige = conversKeytext(key);

        std::cout << keyConfige << std::endl;
        data[keyConfige] = value;

        std::cout << value << std::endl;

        // std::cout << line << std::endl;
    }


    std::string line;
    std::getline(file, line);
    std::cout << line << std::endl;

    std::map<int, std::string> data;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string key;
        std::string value;

        std::getline(ss, key, ',');
        std::getline(ss, value, ',');
        int keyConfige = conversKey(key);

        std::cout << keyConfige << std::endl;
        data[keyConfige] = value;

        std::cout << value << std::endl;

        // std::cout << line << std::endl;
    }
    file.close();
    std::map<int, std::string>::iterator it;
    for (it = data.begin(); it != data.end(); ++it)
    {
        std::cout << "Key: " << it->first
                  << "  |  Value: " << it->second << std::endl;
    }
}