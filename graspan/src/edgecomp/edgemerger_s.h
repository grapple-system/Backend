#ifndef EDGEMERGER_S_H
#define EDGEMERGER_S_H

#include <iostream>
#include <algorithm>
#include <ctime>
#include <limits>

#include "../datastructures/minset.h"
#include "../../test/timer.h"
#include "../utilities/globalDefinitions.hpp"

class EdgeMerger_s
{
	int currVID;

	vector<char> currEvals;

	bool find_val(vector<char> &evals, char val);

	void removeExtraSpace(vector<int> &edges, vector<char> &vals, vector<PseudoPC> &constrs);

	void updateMinSet(MinSet &minset, vector<int> &edges, vector<char> &vals, vector<PseudoPC> &constrs);

	void processMinSets(MinSet &ms1, MinSet &ms2, vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,  vector< vector<PseudoPC> > &constrVecsToMerge, vector<int> &dstEdges, vector<char> &dstVals, vector<PseudoPC> &dstConstrs);

	public:
	// constructor
	EdgeMerger_s();

	void mergeVectors(vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,  vector< vector<PseudoPC> > &constrVecsToMerge);

};

#endif
