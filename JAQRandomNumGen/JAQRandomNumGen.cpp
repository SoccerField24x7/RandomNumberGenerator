// JAQRandomNumGen.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "stdafx.h"
#include "RandomNumberGenerator.h"


int main(int argc, char *argv[])
{
	RandomNumberGenerator *rng = new RandomNumberGenerator(1, 500000);	
	std::vector<long> valArray = rng->GenerateMultiple(100000);

	std::vector<long> uniqueNums = rng->GetUniqueNumbers(valArray);
	std::vector<long> topMatches = rng->GetTopNumbers(valArray);

    return 0;
}

