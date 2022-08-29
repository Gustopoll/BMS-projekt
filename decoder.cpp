#include "decoder.h"

Decoder::Decoder(std::deque<double> input, std::deque<int> inputOrder)
{
    int index = input.size()-1;
    int count = 0;

    while (index > 0)
    {
        y.push_back(input[index]);
        y1.push_back(input[index-1]);
        y2.push_back(input[index-2]);
        LLR_ext.push_back(0);
        index = index -3;
        count++;
    }
    blocksize = count;
    this->inputOrder = inputOrder;
    s1 = new SISO_Decoder(blocksize);
    s2 = new SISO_Decoder(blocksize);
}

std::deque<int> Decoder::execute()
{
    for (unsigned i = 0; i < 16; i++) 
        if (iterate() == true)
            break;
    return hard_decision(LLR_ext);
}

bool Decoder::iterate()
{
    auto out1 = s1->execute(y,y1,LLR_ext);

    out1 = sub(out1,LLR_ext);
    out1 = sub(out1,mul(y,2));
    Interleaver interleaver(inputOrder);
    auto LLR_interleaved = interleaver.execute(out1);

    auto y_interleaved = interleaver.execute(y);
    
    auto out2 = s2->execute(y_interleaved,y2,LLR_interleaved);

    out2 = sub(out2,LLR_interleaved);
    out2 = sub(out2,mul(y_interleaved,2));

    LLR_ext = interleaver.de_execute(out2);

    return early_exit(out1,LLR_ext);
}

bool Decoder::early_exit(std::deque<double> v1, std::deque<double> v2)
{
    for (int i = 0; i < (int)v1.size(); i++)
    {
        if ((v1[i] > 0) && (v2[i] <= 0))
            return false;
        if ((v1[i] <= 0) && (v2[i] > 0))
            return false;
    }
    return true;
}

std::deque<double> Decoder::mul(std::deque<double> v, int number)
{
    for (int i = 0; i < (int)v.size(); i++)
        v[i] = v[i] * 2;
    return v;
}

std::deque<double> Decoder::sub(std::deque<double> v1, std::deque<double> v2)
{
    for (int i = 0; i < (int)v1.size(); i++)
        v1[i] = v1[i] - v2[i];
    return v1;
}

std::deque<int> Decoder::hard_decision(std::deque<double> input)
{
    std::deque<int> result;
    for (unsigned i = 0; i < input.size(); i++)
    {
        if (input[i] >= 0)
            result.push_back(1);
        else
            result.push_back(0);
    }
    return result;
}