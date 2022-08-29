#pragma once
#include <string>
#include <deque>
#include <iostream>

struct Tuple
{
    int t1;
    int t2;
};

class Trellis
{
public:
	Trellis();

    std::deque<Tuple> possibleTransitions;
    std::deque<Tuple> pastStates;
    std::deque<Tuple> futureStates;

    Tuple GetSymbolTransitionMatrix(int x, int y);
    double Butterfly(double a1,double a2,double b1,double b2);

private:
    std::deque<Tuple> transitionMatrix;
};
