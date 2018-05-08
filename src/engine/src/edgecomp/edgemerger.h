#ifndef EDGEMERGER_H
#define EDGEMERGER_H

#include <iostream>
#include <algorithm>
#include <ctime>
#include <limits>
#include <unordered_set>
#include <queue>

#include "../../../constraint/pseudoPC.hpp"
#include "../../../constraint/seg.hpp"
#include "../../../constraint/realPC.hpp"

#include "../datastructures/minset.h"
#include "../../test/timer.h"
#include "../utilities/globalDefinitions.hpp"


class EdgeMerger
{
	int deltaPtr;		// index into the vector of new edges
	int oUnUdPtr;		// index into the vector of ALL edges
	int currID;			// the current vertex ID (increasing order)

	vector<label_t> currEvals;		// the current edge values (to check for duplicates)
	std::priority_queue<MinSet, vector<MinSet>, compare> minEdges;		// finds the minset with the minimum current vertex ID


	// FUNCTIONS
	void fillPriorityQueue(vector< vector<vertexid_t> > &edgeVecsToMerge, vector< vector<label_t> > &valVecsToMerge,
			vector<vertexid_t> &srcDeltaEdges, vector<label_t> &srcDeltaVals, vector<vertexid_t> &srcoUnUdEdges, vector<label_t> &srcoUnUdVals,
			int srcID);

	bool find_val(vector<label_t> &evals, char val);

	void removeExtraSpace(vector<vertexid_t> &srcDeltaEdges, vector<label_t> &srcDeltaVals, vector<vertexid_t> &srcoUnUdEdges, vector<label_t> &srcoUnUdVals);

	void updateMinSet(MinSet &minset, vector<vertexid_t> &edges, vector<label_t> &vals);

	void processMinSets(MinSet &srcMS, MinSet &tgtMS, vector<vertexid_t> &srcEdgesToMerge,
		vector<label_t> &srcValsToMerge, vector<vertexid_t> &tgtEdgesToMerge,
		vector<label_t> &tgtValsToMerge, vector<vertexid_t> &srcDeltaEdges, vector<label_t> &srcDeltaVals,
		vector<vertexid_t> &srcoUnUdEdges, vector<label_t> &srcoUnUdVals);

	void updateVector(int vid, char val, vector<vertexid_t> &edges, vector<label_t> &vals, int &ptr);

	public:
	// constructor
	EdgeMerger();

	// getters
	inline int getNumNewEdges() { return deltaPtr + 1; }

	// given all new edges and their values, merge with the source creating a vector of old U new edges
	// and only new edges
void mergeVectors(vector< vector<vertexid_t> > &edgeVecsToMerge,
		vector< vector<label_t> > &valVecsToMerge,  vector< vector<PseudoPC> > &constrVecsToMerge,
		vector<vertexid_t> &srcDeltaEdges, vector<label_t> &srcDeltaVals, vector<PseudoPC> &srcDeltaConstrs,
		vector<vertexid_t> &srcoUnUdEdges, vector<label_t> &srcoUnUdVals,
			vector<PseudoPC> &srcoUnUdConstrs, vertexid_t srcID);

};

#endif
