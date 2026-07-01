#include "RPN.hpp"

RPN::RPN(){};
RPN::~RPN(){};

RPN::RPN(const RPN &op)
{
    _stack = op._stack;
}

RPN &RPN::operator=(const RPN &op)
{
    if(this  != &op)
    {
        _stack = op._stack;
    }
    return *this;
}

bool RPN::isOperator(const std::string &tokin)
{
    return(tokin == "+" || tokin == "-" || tokin == "*" || tokin == "/");
}
bool RPN::tchekNumber(const std::string &token)
{
   return (token.length() == 1 && token[0] >= '0' && token[0] <= '9');
}
double RPN::makeOperation(double a, double b, const std::string &op)
{
    if(op == "+")
        return a + b;
    if(op == "-")
        return a - b;
    if(op == "*")
        return a * b;
    if(op == "/")
    {
        if(b == 0)
        {
            std::cout << "Error: division by zero" << std::endl;
            return 0;
        }
        return a / b;
    }
    return 0;
}
void RPN::calculate(const std::string &expression)
{
    std::stringstream ss(expression);
    std::string token;

    while (ss >> token)
    {
        if (tchekNumber(token))
        {
            int num = atoi(token.c_str());
            _stack.push(num);
        }
        else if (isOperator(token))
        {
            if (_stack.size() < 2)
            {
                std::cerr << "Error" << std::endl;
                return;
            }
            double b = _stack.top();
            _stack.pop();
            double a = _stack.top();
            _stack.pop();

            _stack.push(makeOperation(a, b, token));
        }
        else
        {
            std::cerr << "Error" << std::endl;
            return;
        }
    }

    if (_stack.size() != 1)
    {
        std::cerr << "Error" << std::endl;
        return;
    }
     std::cout << _stack.top() << std::endl;
}