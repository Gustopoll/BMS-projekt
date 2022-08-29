#include "rsc.h"

RSC::RSC(std::deque<int> input)
{
    this->input = input;
    this->state = 0;
}

std::deque<int> RSC::execute()
{
    std::deque<int> result;
    state = 0;
    for (unsigned i = 0; i < input.size(); i++)
    {
        int value = modify(input[i]);
        result.push_back(value);
    }
    return result;
}

std::deque<int> RSC::getBitState()
{
    if (state == 0)
        return std::deque<int> {0,0};
    if (state == 1)
        return std::deque<int> {0,1};
    if (state == 2)
        return std::deque<int> {1,0};
    if (state == 3)
        return std::deque<int> {1,1};

    return std::deque<int>();
}

int RSC::modify(int in)
{
    //STATE 0
    if ((state == 0) && (in == 0))
    {
        state = 0;
        return 0;
    }
    if ((state == 0) && (in == 1))
    {
        state = 2;
        return 1;
    }

    //STATE 1
    if ((state == 1) && (in == 0))
    {
        state = 2;
        return 1;
    }
    if ((state == 1) && (in == 1))
    {
        state = 0;
        return 0;
    }

    //STATE 2
    if ((state == 2) && (in == 0))
    {  
        state = 1;
        return 0;
    }
    if ((state == 2) && (in == 1))
    {
        state = 3;
        return 1;
    }

    //STATE 3
    if ((state == 3) && (in == 0))
    {
        state = 3;
        return 1;
    }
    if ((state == 3) && (in == 1))
    {
        state = 1;
        return 0;
    }
    return -1;
}
