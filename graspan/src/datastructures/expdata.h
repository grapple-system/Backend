#ifndef EXPDATA_H
#define EXPDATA_H

#include "../utilities/globalDefinitions.hpp"

class ExpData
{
	public:
	unsigned long long compTime;
	unsigned long long constrTime;
	long numSolves;
	long numTrues;
	long numEmptyPPCs;
	long numCacheHits;

	ExpData() {};

	void reset();

};

#endif
