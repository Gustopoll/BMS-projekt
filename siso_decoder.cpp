#include "siso_decoder.h"
#include <limits>

SISO_Decoder::SISO_Decoder(int blocksize)
{
    this->blocksize = blocksize;

    //init matrix
    for (int i = 0; i < blocksize; i++)
    {
        Matrix4 m = {0,};
        branch_metrics.push_back(m);
        LLR.push_back(0);
    }

    for (int i = 0; i < blocksize+1; i++)
    {
        double minus_inf = -1 * std::numeric_limits<double>::infinity();
        Array4 a = {0,minus_inf,minus_inf,minus_inf};
        forward_metrics.push_back(a);
        backward_metrics.push_back(a);
    }
}

std::deque<double> SISO_Decoder::execute(std::deque<double> y,std::deque<double> yp,std::deque<double> la)
{
    this->y = y;
    this->yp = yp;
    this->la = la;
    compute_branch();

    for (int k = 1; k < blocksize+1; k++)
    {
        for (int state = 0; state < 4; state++)
        {
            compute_forward(k,state);
            compute_backward(k,state);
        }
    }
    for (int k = 0; k < blocksize; k++)
        compute_LLR(k);

    return LLR;
}

void SISO_Decoder::compute_branch()
{
    Trellis trellis;

    for (int k = 0; k < blocksize; k++)
    {
        for (int j = 0; j < (int)trellis.possibleTransitions.size(); j++)
        {
            auto t = trellis.possibleTransitions[j];
            auto s = trellis.GetSymbolTransitionMatrix(t.t1,t.t2);
            branch_metrics[k][t.t1][t.t2] = s.t1 * y[k] + s.t2 * yp[k] + s.t1 * la[k];
        }
    }
}

void SISO_Decoder::compute_forward(int k, int state)
{
    Trellis trellis;
    auto past_state = trellis.pastStates[state];

    auto a1 = forward_metrics[k-1][past_state.t1];
    auto a2 = forward_metrics[k-1][past_state.t2];

    auto b1 = branch_metrics[k-1][past_state.t1][state];
    auto b2 = branch_metrics[k-1][past_state.t2][state];

    forward_metrics[k][state] = trellis.Butterfly(a1,a2,b1,b2);
}

void SISO_Decoder::compute_backward(int k, int state)
{
    Trellis trellis;
    auto future_state = trellis.futureStates[state];

    int r = blocksize - k;
    auto a1 = backward_metrics[k-1][future_state.t1];
    auto a2 = backward_metrics[k-1][future_state.t2];

    auto b1 = branch_metrics[r][state][future_state.t1];
    auto b2 = branch_metrics[r][state][future_state.t2];

    backward_metrics[k][state] = trellis.Butterfly(a1,a2,b1,b2);
}

void SISO_Decoder::compute_LLR(int k)
{
    Trellis trellis;
    int r = blocksize - k - 1;

    std::deque<double> pos;
    std::deque<double> neg;


    for (int j = 0; j < (int)trellis.possibleTransitions.size(); j++)
    {
        auto t = trellis.possibleTransitions[j];
        auto s = trellis.GetSymbolTransitionMatrix(t.t1,t.t2);

        auto a1 = forward_metrics[k][t.t1];
        auto a2 = branch_metrics[k][t.t1][t.t2];
        auto a3 = backward_metrics[r][t.t2];

        if (s.t1 < 0)
        {
            neg.push_back(a1 + a2 + a3);
        }
        else
        {
            pos.push_back(a1 + a2 + a3);
        }
    }

    double maxPos = *std::max_element(pos.begin(),pos.end());
    double maxNeg = *std::max_element(neg.begin(),neg.end());

    LLR[k] = (maxPos - maxNeg);
}