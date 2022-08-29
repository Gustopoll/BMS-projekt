#pragma once
#include <string>
#include <deque>
#include <iostream>

#include "rsc.h"
#include "interleaver.h"

class Encoder
{
public:
	Encoder(std::deque<int> input,std::deque<int> inputOrder);

    std::deque<int> execute();
private:
    std::deque<int> input;
    Interleaver* interleaver;
};
