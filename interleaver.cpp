#include "interleaver.h"


Interleaver::Interleaver(std::deque<int> inputOrder)
{
    this->inputOrder = inputOrder;
}


std::deque<int> Interleaver::execute(std::deque<int> input)
{
    std::deque<int> result;
    int sizeOfInput = inputOrder.size()-1; //this is because inputOrder is reversed

    for (unsigned i = 0; i < inputOrder.size(); i++)
    {
        int value = input[inputOrder[sizeOfInput-i]];
        result.push_back(value);
    }

    return result;
}

std::deque<double> Interleaver::execute(std::deque<double> input)
{
    std::deque<double> result;
    int sizeOfInput = inputOrder.size()-1; //this is because inputOrder is reversed

    for (unsigned i = 0; i < inputOrder.size(); i++)
    {
        double value = input[inputOrder[sizeOfInput-i]];
        result.push_back(value);
    }

    return result;
}

std::deque<int> Interleaver::de_execute(std::deque<int> input)
{
    std::deque<int> result = input;
    int sizeOfInput = inputOrder.size()-1; //this is because inputOrder is reversed

    for (unsigned i = 0; i < inputOrder.size(); i++)
    {
        int value = input[i];
        result[inputOrder[sizeOfInput-i]] = value;
    }

    return result;
}

std::deque<double> Interleaver::de_execute(std::deque<double> input)
{
    std::deque<double> result;
    int sizeOfInput = inputOrder.size()-1; //this is because inputOrder is reversed

    for (unsigned i = 0; i < inputOrder.size(); i++)
    {
        result.push_back(input[i]);
    }

    for (unsigned i = 0; i < inputOrder.size(); i++)
    {
        double value = input[i];
        result[inputOrder[sizeOfInput-i]] = value;
    }

    return result;

}