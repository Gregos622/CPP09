#pragma once

#include <vector>
#include <deque>

class PmergeMe
{
public:
    PmergeMe();
    ~PmergeMe();

    void run(int argc, char **argv);

private:
    std::vector<int> _vec;
    std::deque<int>  _deq;

    void parseInput(int argc, char **argv);

    void sortVector();
    void sortDeque();

    void fordJohnsonVector(std::vector<int>& v);
    void fordJohnsonDeque(std::deque<int>& d);

    int  binaryInsertPos(const std::vector<int>& v, int value);
    int  binaryInsertPos(const std::deque<int>& d, int value);

    void printBefore() const;
    void printAfter(const std::vector<int>& v) const;
};

