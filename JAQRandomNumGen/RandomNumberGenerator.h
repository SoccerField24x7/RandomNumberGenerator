#pragma once
#include <vector>
#include <random>
#include <map>

class RandomNumberGenerator
{
private:
	long _high;
	long _low;
	std::vector<long> _result;
	std::mt19937 _mTwister;
	std::uniform_real_distribution<double> _dist;
	void Init();
public:
	RandomNumberGenerator();
	RandomNumberGenerator(long, long);
	~RandomNumberGenerator();
	long GenerateNumber();
	std::vector<long> GenerateMultiple(long);
	bool setBounds(long, long);
	std::vector<long> GetUniqueNumbers(std::vector<long>);
	std::vector<long> SortResults(std::vector<long>, std::string);
	std::vector<long> SortResults(std::vector<long>);
	std::vector<long> GetTopNumbers(std::vector<long>);
};

