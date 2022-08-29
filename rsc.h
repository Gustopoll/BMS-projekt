#pragma once
#include <string>
#include <deque>
#include <iostream>

class RSC
{
public:
	RSC(std::deque<int> input);

    std::deque<int> execute();
    std::deque<int> getBitState();
private:
    //this function represent trellis graph
    int modify(int in);

    std::deque<int> input;
    int state;

};
