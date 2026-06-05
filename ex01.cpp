#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <cstdlib>


int main(int ac, char **av)
{
    if(ac != 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
        
    std::stack<double> total;
    std::stringstream ss(av[1]);
    std::string inp;
    while (ss >> inp)
    {
        if(inp.length() == 1 && isdigit(inp[0]))
            total.push(atof(inp.c_str()));
        else if(inp == "+" || inp == "-" || inp == "*" || inp == "/")
        {
            if(total.size() < 2)
            {
                std::cout << "Error" << std::endl;
            }
            
        }
    }
    



}
