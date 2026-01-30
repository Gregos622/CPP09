#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        std::istringstream iss(argv[i]);
        int n;
        char c;

        if (!(iss >> n) || (iss >> c) || n < 0)
            throw std::runtime_error("Error");

        _vec.push_back(n);
        _deq.push_back(n);
    }
}

void PmergeMe::printBefore() const
{
    std::cout << "Before: ";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::printAfter(const std::vector<int>& v) const
{
    std::cout << "After: ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

int PmergeMe::binaryInsertPos(const std::vector<int>& v, int value)
{
    int left = 0, right = v.size();
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (v[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

int PmergeMe::binaryInsertPos(const std::deque<int>& d, int value)
{
    int left = 0, right = d.size();
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (d[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void PmergeMe::fordJohnsonVector(std::vector<int>& v)
{
    if (v.size() <= 1)
        return;

    std::vector<int> main;
    std::vector<int> pend;

    for (size_t i = 0; i + 1 < v.size(); i += 2)
    {
        if (v[i] > v[i + 1])
        {
            main.push_back(v[i]);
            pend.push_back(v[i + 1]);
        }
        else
        {
            main.push_back(v[i + 1]);
            pend.push_back(v[i]);
        }
    }

    if (v.size() % 2 != 0)
        pend.push_back(v.back());

    fordJohnsonVector(main);

    for (size_t i = 0; i < pend.size(); ++i)
    {
        int pos = binaryInsertPos(main, pend[i]);
        main.insert(main.begin() + pos, pend[i]);
    }

    v = main;
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& d)
{
    if (d.size() <= 1)
        return;

    std::deque<int> main;
    std::deque<int> pend;

    for (size_t i = 0; i + 1 < d.size(); i += 2)
    {
        if (d[i] > d[i + 1])
        {
            main.push_back(d[i]);
            pend.push_back(d[i + 1]);
        }
        else
        {
            main.push_back(d[i + 1]);
            pend.push_back(d[i]);
        }
    }

    if (d.size() % 2 != 0)
        pend.push_back(d.back());

    fordJohnsonDeque(main);

    for (size_t i = 0; i < pend.size(); ++i)
    {
        int pos = binaryInsertPos(main, pend[i]);
        main.insert(main.begin() + pos, pend[i]);
    }

    d = main;
}

void PmergeMe::sortVector()
{
    clock_t start = clock();
    fordJohnsonVector(_vec);
    clock_t end = clock();

    double us = (double)(end - start) * 1e6 / CLOCKS_PER_SEC;
	printAfter(_vec);
    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << us << " us" << std::endl;
}

void PmergeMe::sortDeque()
{
    clock_t start = clock();
    fordJohnsonDeque(_deq);
    clock_t end = clock();

    double us = (double)(end - start) * 1e6 / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque : " << us << " us" << std::endl;
}

void PmergeMe::run(int argc, char **argv)
{
    parseInput(argc, argv);
    printBefore();
    sortVector();
    //printAfter(_vec);
    sortDeque();
}
