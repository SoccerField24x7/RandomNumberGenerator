// JAQRandomNumGen.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "stdafx.h"
#include "RandomNumberGenerator.h"


int main(int argc, char *argv[])
{

	std::vector<long> tstArray(5);
	tstArray[0] = 300;
	tstArray[1] = 300;
	tstArray[2] = 400;
	tstArray[3] = 400;
	tstArray[4] = 1000;

	RandomNumberGenerator *rng = new RandomNumberGenerator(1, 500000);
	long val = rng->GenerateNumber();

	std::vector<long> vals = rng->GenerateMultiple(25);
		
	rng->SortResults(vals, "dEsC");

	rng->SortResults(vals);

	try 
	{
		rng->SortResults(vals, "TEST");
	}
	catch (const std::exception& ex) 
	{
		std::cout << ex.what();
	}

	std::vector<long> trimmed = rng->GetUniqueNumbers(tstArray);

	std::vector<long> topMatches = rng->GetTopNumbers(tstArray);

    return 0;
}

