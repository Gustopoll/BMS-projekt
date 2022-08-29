#pragma once
#include <string>
#include <deque>
#include <iostream>

class Interleaver
{
public:
	Interleaver(std::deque<int> inputOrder);

    std::deque<int> execute(std::deque<int> input);
    std::deque<double> execute(std::deque<double> input);

    std::deque<int> de_execute(std::deque<int> input);
    std::deque<double> de_execute(std::deque<double> input);
private:
        std::deque<int> inputOrder;


};
