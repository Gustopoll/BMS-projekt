#include <iostream>
#include <string>
#include <deque>
#include <cstring>

#include "encoder.h"
#include "decoder.h"

enum class TypeCoder {
	ENCODE,
	DECODE,
	NONE
};

std::deque<int> string_to_deque_of_int(std::string line)
{
	std::deque<int> input;
	for (unsigned i = 0; i < line.size(); i++)
		input.push_back(int(line[i]) - 48);
	return input;
}

template <typename T>
void split(std::string const &str, const char delim, std::deque<T> &out)
{
    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_front( atof(str.substr(start, end - start).c_str()));
    }
}

void ErrorMSG(std::string msg)
{
	std::cerr << msg << "\n";
	exit(1);
}

void printOutput(std::deque<int> y)
{
	for (unsigned i = 0; i < y.size(); i++)
	{
		std::cout << y[i];
	}
	std::cout << "\n";
}

void printHelp()
{
	std::cout << "BMS projekt\n";
	std::cout << "run: ./bms <type> -i <interleaver> <<< [input] \n";
	std::cout << "type:\t-e = encoder - input bits\n";
	std::cout << "\t-d = decoder - input real number\n";
	exit(0);
}
int main(int argc, char *argv[])
{
	std::string inputArgument; /// -i 0,2,1
	TypeCoder codingType = TypeCoder::NONE;
	
	if (argc <= 1)
		printHelp();

	//LOAD INPUT
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i],"-h") == 0)
		{
			printHelp();
		}
		if (strcmp(argv[i],"-e") == 0)
		{
			codingType = TypeCoder::ENCODE;
		}
		if (strcmp(argv[i],"-d") == 0)
		{
			codingType = TypeCoder::DECODE;
		}
		if (strcmp(argv[i],"-i") == 0)
		{
			if (i+1 == argc)
				ErrorMSG("Missing value\n");

			inputArgument = argv[i+1];
		}
	}
	
	// ENCODING AND DECODING
	if (codingType == TypeCoder::NONE)
		ErrorMSG("Missing param -e or -d, try -h for help");

	std::string inputPipeline; /// <<< 101 or 0.5,0.4
	std::cin >> inputPipeline;
	std::deque<int> inputEncode;
	std::deque<double> inputDecode;
	std::deque<int> order;
	split(inputArgument,',',order);

	if (codingType == TypeCoder::ENCODE) //ENCODING
	{
		inputEncode = string_to_deque_of_int(inputPipeline);
		Encoder encoder(inputEncode,order);
		auto result = encoder.execute();
		printOutput(result);
	}
	

	if (codingType == TypeCoder::DECODE) //DECODING
	{
		split(inputPipeline,',',inputDecode);
		Decoder decoder(inputDecode, order);
		auto result = decoder.execute();
		printOutput(result);
	}


	return 0;
}
