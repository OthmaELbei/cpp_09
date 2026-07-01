#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <cstdlib>

class RPN
{
private:
	std::stack<double> _stack;

public:
	bool isOperator(const std::string &token);
	bool tchekNumber(const std::string &token);
	double makeOperation(double a, double b, const std::string &op);

	RPN();
	~RPN();
	RPN(const RPN &op);
	RPN &operator=(const RPN &other);
	void calculate(const std::string &expression);
};

#endif