#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _size(0) {}
PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
	: _vec(other._vec), _deq(other._deq), _size(other._size) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
		_size = other._size;
	}
	return *this;
}

bool PmergeMe::parseInput(int ac, char **av)
{
	if (ac < 2)
		return false;
	for (int i = 1; i < ac; i++)
	{
		std::string s(av[i]);
		if (s.empty())
			return false;
		for (size_t j = 0; j < s.length(); j++)
		{
			if (s[j] < '0' || s[j] > '9')
				return false;
		}
		long num = std::atol(av[i]);
		if (num < 0 || num > 2147483647)
			return false;
		_vec.push_back(static_cast<int>(num));
		_deq.push_back(static_cast<int>(num));
	}
	_size = static_cast<int>(_vec.size());
	return _size > 0;
}

std::vector<int> PmergeMe::jacobsthalSeq(int n)
{
	std::vector<int> res;
	res.push_back(0);
	res.push_back(1);
	int a = 0;
	int b = 1;
	int k = 2 * a + b;
	while (k <= n)
	{
		res.push_back(k);
		a = b;
		b = k;
		k = 2 * a + b;
	}
	return res;
}

void PmergeMe::mergeSortVec(std::vector<std::pair<int, int>> &v)
{
	if (v.size() <= 1)
		return;
	std::vector<std::pair<int, int>> l, r;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (i < v.size() / 2)
			l.push_back(v[i]);
		else
			r.push_back(v[i]);
	}
	mergeSortVec(l);
	mergeSortVec(r);
	for (size_t i = 0, j = 0, k = 0; i < l.size() || j < r.size(); k++)
	{
		if (j == r.size())
		{
			v[k] = l[i];
			i++;
		}
		else if (i == l.size())
		{
			v[k] = r[j];
			j++;
		}
		else if (l[i].first < r[j].first)
		{
			v[k] = l[i];
			i++;
		}
		else
		{
			v[k] = r[j];
			j++;
		}
	}
}

double PmergeMe::sortVector()
{
	clock_t start = clock();

	if (_vec.size() <= 1)
		return static_cast<double>(clock() - start) / CLOCKS_PER_SEC * 1000000;

	std::vector<std::pair<int, int>> w;
	int straggler = -1;
	bool hasStraggler = (_vec.size() % 2 != 0);
	if (hasStraggler)
		straggler = _vec.back();

	for (int i = 1; i < _vec.size(); i += 2)
	{
		w.push_back(std::make_pair(
			std::max(_vec[i], _vec[i - 1]),
			std::min(_vec[i], _vec[i - 1])));
	}

	mergeSortVec(w);

	std::vector<int> mainChain;
	std::vector<int> pend;
	for (size_t i = 0; i < w.size(); i++)
	{
		mainChain.push_back(w[i].first);
		pend.push_back(w[i].second);
	}

	std::vector<int> jacob = jacobsthalSeq(static_cast<int>(pend.size()));
	int cnt = 0;
	int prev = -1;
	for (size_t i = 0; i < jacob.size(); i++)
	{
		int next = std::min(static_cast<int>(pend.size()) - 1, jacob[i]);
		for (int j = next; j > prev; j--)
		{
			std::vector<int>::iterator it = std::upper_bound(
				mainChain.begin(), mainChain.begin() + j + cnt, pend[j]);
			mainChain.insert(it, pend[j]);
			cnt++;
		}
		prev = next;
	}
	if (hasStraggler)
	{
		std::vector<int>::iterator it = std::upper_bound(
			mainChain.begin(), mainChain.end(), straggler);
		mainChain.insert(it, straggler);
	}

	_vec = mainChain;
	return static_cast<double>(clock() - start) / CLOCKS_PER_SEC * 1000000;
}

void PmergeMe::mergeSortDeq(std::deque<std::pair<int, int>> &v)
{
	if (v.size() <= 1)
		return;
	std::deque<std::pair<int, int>> l, r;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (i < v.size() / 2)
			l.push_back(v[i]);
		else
			r.push_back(v[i]);
	}
	mergeSortDeq(l);
	mergeSortDeq(r);
	for (size_t i = 0, j = 0, k = 0; i < l.size() || j < r.size(); k++)
	{
		if (j == r.size())
		{
			v[k] = l[i];
			i++;
		}
		else if (i == l.size())
		{
			v[k] = r[j];
			j++;
		}
		else if (l[i].first < r[j].first)
		{
			v[k] = l[i];
			i++;
		}
		else
		{
			v[k] = r[j];
			j++;
		}
	}
}

double PmergeMe::sortDeque()
{
	clock_t start = clock();

	if (_deq.size() <= 1)
		return static_cast<double>(clock() - start) / CLOCKS_PER_SEC * 1000000;

	std::deque<std::pair<int, int>> w;
	int straggler = -1;
	bool hasStraggler = (_deq.size() % 2 != 0);
	if (hasStraggler)
		straggler = _deq.back();

	for (size_t i = 1; i < _deq.size(); i += 2)
		w.push_back(std::make_pair(
			std::max(_deq[i], _deq[i - 1]),
			std::min(_deq[i], _deq[i - 1])));

	mergeSortDeq(w);

	std::deque<int> mainChain;
	std::deque<int> pend;
	for (size_t i = 0; i < w.size(); i++)
	{
		mainChain.push_back(w[i].first);
		pend.push_back(w[i].second);
	}

	std::vector<int> jacob = jacobsthalSeq(static_cast<int>(pend.size()));
	int cnt = 0;
	int prev = -1;
	for (size_t i = 0; i < jacob.size(); i++)
	{
		int next = std::min(static_cast<int>(pend.size()) - 1, jacob[i]);
		for (int j = next; j > prev; j--)
		{
			std::deque<int>::iterator it = std::upper_bound(
				mainChain.begin(), mainChain.begin() + j + cnt, pend[j]);
			mainChain.insert(it, pend[j]);
			cnt++;
		}
		prev = next;
	}

	if (hasStraggler)
	{
		std::deque<int>::iterator it = std::upper_bound(
			mainChain.begin(), mainChain.end(), straggler);
		mainChain.insert(it, straggler);
	}

	_deq.assign(mainChain.begin(), mainChain.end());
	return static_cast<double>(clock() - start) / CLOCKS_PER_SEC * 1000000;
}

void PmergeMe::run()
{
	std::cout << "Before:";
	for (size_t i = 0; i < _vec.size(); i++)
		std::cout << " " << _vec[i];
	std::cout << std::endl;

	double timeVec = sortVector();
	double timeDeq = sortDeque();

	std::cout << "After:";
	for (size_t i = 0; i < _vec.size(); i++)
		std::cout << " " << _vec[i];
	std::cout << std::endl;

	std::cout << "Time to process a range of " << _size
			  << " elements with std::vector : " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << _size
			  << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}