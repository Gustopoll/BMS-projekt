#include "encoder.h"

Encoder::Encoder(std::deque<int> input,std::deque<int> inputOrder)
{
    this->input = input;
    interleaver = new Interleaver(inputOrder);
}

std::deque<int> Encoder::execute()
{
    std::deque<int> result;

    auto y2 = interleaver->execute(input);

    RSC rsc2(y2);
    auto y2result = rsc2.execute();
    auto y2register = rsc2.getBitState();

    RSC rsc1(input);
    auto y1result = rsc1.execute();
    auto y1register = rsc1.getBitState();

    for (unsigned i = 0; i < input.size(); i++)
	{
		result.push_back(input[i]);
        result.push_back(y1result[i]);
        result.push_back(y2result[i]);
	}

    //register values
    int size = input.size() - 1;
    result.push_back(y1result[size - 1]);
    result.push_back(y1register[1]);
    result.push_back(y2register[1]);
    result.push_back(y1result[size]);
    result.push_back(y1register[0]);
    result.push_back(y2register[0]);
    return result;
}