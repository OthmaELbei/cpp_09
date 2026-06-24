#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>

class PmergeMe
{
private:
    std::vector<int> _vec;
    std::deque<int>  _deq;
    int              _size;

    // vector
    void   mergeSortVec(std::vector<std::pair<int,int> >& v);
    double sortVector();

    // deque
    void   mergeSortDeq(std::deque<std::pair<int,int> >& d);
    double sortDeque();

    std::vector<int> jacobsthalSeq(int n);

    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);

public:
    PmergeMe();
    ~PmergeMe();

    bool parseInput(int ac, char **av);
    void run();
};

#endif