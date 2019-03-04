#include "expdata.h"

void ExpData::reset() {
	compTime=0;
	constrTime=0;
	numSolves=0;
	numTrues=0;
	numEmptyPPCs=0;
	numCacheHits=0;
}
