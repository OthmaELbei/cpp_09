#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    PmergeMe sorter;

    if (!sorter.parseInput(ac, av))
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    sorter.run();
    return 0;
}