#pragma once
#include <string>
#include <deque>
#include <iostream>

#include "siso_decoder.h"
#include "interleaver.h"


class Decoder
{
public:
	Decoder(std::deque<double> input, std::deque<int> inputOrder);

    std::deque<int> execute();
private:
    bool iterate();
    bool early_exit(std::deque<double> v1, std::deque<double> v2);
    std::deque<double> mul(std::deque<double> v, int number);
    std::deque<double> sub(std::deque<double> v1, std::deque<double> v2);
    std::deque<int> hard_decision(std::deque<double> input);

    std::deque<double> y;
    std::deque<double> y1;
    std::deque<double> y2;
    std::deque<double> LLR_ext;
    std::deque<int> inputOrder;
    int blocksize;

    SISO_Decoder *s1;
    SISO_Decoder *s2;
};
