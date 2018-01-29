#include "RandomNumberGenerator.h"
#include <vector>
#include <random>
#include <iostream>
#include <functional>
#include <algorithm>
#include <map>
#include <iterator>

RandomNumberGenerator::RandomNumberGenerator()
{
	setBounds(1, 10);  //default constructure gives a number between 1 and 10
}

RandomNumberGenerator::RandomNumberGenerator(long lowValue, long highValue)
{
	if (!setBounds(lowValue, highValue))
		throw std::invalid_argument("Values out of bounds.");
}

RandomNumberGenerator::~RandomNumberGenerator()
{
	//is there anything to free??
}

bool RandomNumberGenerator::setBounds(long lowValue, long highValue)
{
	if (lowValue > highValue)
		return false;

	_high = highValue;
	_low = lowValue;
	_highCount = 0;

	Init();

	return true;
}

void RandomNumberGenerator::Init()
{	
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(_low, _high);

	_mTwister = mt;
	_dist = dist;
}

long RandomNumberGenerator::GenerateNumber()
{	
	return _dist(_mTwister);
}

std::vector<long> RandomNumberGenerator::GenerateMultiple(long qty)
{
	std::vector<long> list; //create a vector that will hold all of the generated numbers
	list.reserve(qty);

	for (int i = 0; i < qty; i++)
		list.push_back(GenerateNumber());
		
	return _result = list;  //store vector for later reference, if necessary, and return
}

std::vector<long> RandomNumberGenerator::GetUniqueNumbers(std::vector<long> arry)
{
	arry = SortResults(arry); //created method to allow ascending or descending
	arry.erase(std::unique(arry.begin(), arry.end()), arry.end());
	return arry;
}

/**
*
*/
std::vector<long> RandomNumberGenerator::SortResults(std::vector<long> arry, std::string sortDir) //ASC or DESC
{
	//standardize the input
	std::transform(sortDir.begin(), sortDir.end(), sortDir.begin(), toupper);
	
	//ensure we have acceptable parameters
	if(sortDir.compare("DESC") != 0 && sortDir.compare("ASC") != 0)
		throw std::invalid_argument("Sort Type must be ASC or DESC");

	if (sortDir.compare("DESC") == 0)
		sort(arry.begin(), arry.end(), std::greater<long>());
	else
		sort(arry.begin(), arry.end());

	return arry;
}
/**
	Skinny overload to allow a default sort order

	@author Jesse Quijano
*/
std::vector<long> RandomNumberGenerator::SortResults(std::vector<long> arry)
{
	return SortResults(arry, "ASC");
}

/** Because of the limitations with sorting a map, borrowed this clean solution to flip the positions allowing sort on total.
No sense re-inventing the wheel.

https://stackoverflow.com/a/5056797/1732853
*/
template<typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B> &p)
{
	return std::pair<B, A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B, A> flip_map(const std::map<A, B> &src)
{
	std::multimap<B, A> dst;
	std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
		flip_pair<A, B>);
	return dst;
}
/* end */
std::vector<long> RandomNumberGenerator::GetTopNumbers(std::vector<long> arry)
{
	std::map<long,int> uniques;
	std::vector<long> tops;

	//uniques and counts, voila!
	for_each(arry.begin(), arry.end(), [&uniques](long val) { uniques[val]++; });

	//reverse position of the random numbers and counts
	std::multimap<int, long> dst = flip_map(uniques);

	int lastCount = 0;
	for (auto row = dst.rbegin(); row != dst.rend(); ++row) {
		std::cout << row->first << ": " << row->second << std::endl;
		if (lastCount != row->first || _highCount == row->first) {
			
			if (_highCount > 0 && _highCount != row->first)
				break;

			_highCount = row->first;
			tops.push_back(row->second);  //not the most efficient to resize, but there shouldn't be many.
		}

		lastCount = row->first;
	}

	return tops;
}

long RandomNumberGenerator::GetTopMatchCount()
{
	return _highCount;
}

long RandomNumberGenerator::GetRangeHigh()
{
	return _high;
}

long RandomNumberGenerator::GetRangeLow()
{
	return _low;
}

