#pragma once
#include <string>
#include <deque>
#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <cmath>

#include "trellis.h"


typedef std::array<std::array<double,4>,4> Matrix4;
typedef std::array<double,4> Array4;

class SISO_Decoder
{
public:
	SISO_Decoder(int blocksize);

    std::deque<double> execute(std::deque<double> y,std::deque<double> yp,std::deque<double> la);
private:
    void compute_branch();
    void compute_forward(int k, int state);
    void compute_backward(int k, int state);
    void compute_LLR(int k);

    std::deque<double> y;
    std::deque<double> yp;
    std::deque<double> la;
    int blocksize;
    std::deque<double> LLR;

    std::deque<Matrix4> branch_metrics;
    std::deque<Array4> forward_metrics;
    std::deque<Array4> backward_metrics;

};
