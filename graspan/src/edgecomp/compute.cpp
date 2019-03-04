#include "compute.h"
#include "../../test/timer.h"



// FUNCTION DEFINITIONS
long updateEdges(int vertInd, ComputationSet compsets[], LoadedVertexInterval intervals[],
		Context &context, SEGraph* seg, ExpData &expThreadData, LRUCache &cache_lru);

void getEdgesToMerge(ComputationSet *compSet, ComputationSet compsets[],
		LoadedVertexInterval intervals[], bool oldEdgesEmpty, bool newEdgesEmpty,
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,
		vector< vector<PseudoPC> > &constrVecsToMerge, int &rowMergeID, Context &context, SEGraph* seg, ExpData &expThreadData, LRUCache &cache_lru);

void genS_RuleEdges(vector<int> &newEdges, vector<char> &newVals, vector<PseudoPC> &newConstrs,
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,
		vector< vector<PseudoPC> > &constrVecsToMerge, int &rowMergeID, Context &context, SEGraph* seg, ExpData &expThreadData);

void genD_RuleEdges(ComputationSet compsets[], LoadedVertexInterval intervals[], vector<int> &edges,
		vector<char> &vals, vector<PseudoPC> &constrs, vector< vector<int> > &edgeVecsToMerge,
		vector< vector<char> > &valVecsToMerge, vector< vector<PseudoPC> > &constrVecsToMerge,
		int &rowMergeID, Context &context, char flag, SEGraph* seg, ExpData &expThreadData, LRUCache &cache_lru);

void checkEdges(int dstInd, char dstVal, PseudoPC dstConstr, ComputationSet compsets[],
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,
		vector< vector<PseudoPC> > &constrVecsToMerge, int &rowMergeID, Context &context, char flag, SEGraph* seg, ExpData &expThreadData, LRUCache &cache_lru);

// PRINT EDGES FOR DEBUGGING
void print_edges(vector<vector<int>> &edgeVecsToMerge, vector<vector<char>> &valVecsToMerge)
{
	for (int i = 0; i < edgeVecsToMerge.size(); i++)
	{
		if (edgeVecsToMerge[i].size() == 0) cout << "VEC" << i << ": empty..." << endl;
		else {
			cout << "VEC" << i << ": ";
			for (int j = 0; j < edgeVecsToMerge[i].size(); j++)
				cout << "(" << edgeVecsToMerge[i][j] << ", " << (short)valVecsToMerge[i][j] << ")  ";

			cout << endl;
		}
	}
	cout << endl;
}


/**
 * given an index into the compsets, find all valid edges and merge them into a new list
 *
 * @param vertInd			-index of source vertex in compsets[]
 * @param compsets[]		-ComputationSet list for all in-memory vertices
 * @param intervals			-list (size=2) with information about the partitions
 * @param context			-Context object for checking grammar
 */
long updateEdges(int vertInd, ComputationSet compsets[], LoadedVertexInterval intervals[], Context &context, SEGraph* seg, ExpData &expThreadData, LRUCache &cache_lru)
{
	ComputationSet *compSet = &compsets[vertInd];

	bool oldEdgesEmpty = (compSet->getOldEdges().empty()) ? true : false;
	bool newEdgesEmpty = (compSet->getNewEdges().empty()) ? true : false;

	if (oldEdgesEmpty && newEdgesEmpty) return 0;

	// // ESTIMATE the number of vectors we will need to merge
	// vector< vector<double> > &ddm = context.ddm.getDdmMap();
	// int numRowsToMerge = 8;		// place holder because no better heuristic
	// vector< vector<int> > edgeVecsToMerge(numRowsToMerge);
	// vector< vector<char> > valVecsToMerge(numRowsToMerge);
	// vector< vector<PseudoPC> > constrVecsToMerge(numRowsToMerge);

	int numRowsToMerge = 2;
	vector< vector<int> > edgeVecsToMerge(numRowsToMerge);
	vector< vector<char> > valVecsToMerge(numRowsToMerge);
	vector< vector<PseudoPC> > constrVecsToMerge(numRowsToMerge);

	// // set edgeVecsToMerge[0] equal to the current vertex's outgoing edges
	// int rowMergeID = 0;
	// edgeVecsToMerge[rowMergeID] = compSet->getoldUnewEdges();
	// // valVecsToMerge[rowMergeID++] = compSet->getoldUnewVals();
	// valVecsToMerge[rowMergeID] = compSet->getoldUnewVals();
	// constrVecsToMerge[rowMergeID++] = compSet->getoldUnewConstr();

	int rowMergeID = 1;

	// find new edges
	getEdgesToMerge(compSet, compsets, intervals, oldEdgesEmpty, newEdgesEmpty, edgeVecsToMerge, valVecsToMerge, constrVecsToMerge, rowMergeID, context, seg, expThreadData, cache_lru);

	EdgeMerger em;

	edgeVecsToMerge[0] = compSet->getoldUnewEdges();
	valVecsToMerge[0] = compSet->getoldUnewVals();
	constrVecsToMerge[0] = compSet->getoldUnewConstr();

	vector<int> &srcDeltaEdges = compSet->getDeltaEdges();
	vector<char> &srcDeltaVals = compSet->getDeltaVals();
	vector<PseudoPC> &srcDeltaConstrs = compSet->getDeltaConstr();

	vector<int> &srcoUnUdEdges = compSet->getoUnUdEdges();
	vector<char> &srcoUnUdVals = compSet->getoUnUdVals();
	vector<PseudoPC> &srcoUnUdConstrs = compSet->getoUnUdConstr();

	em.mergeVectors(edgeVecsToMerge, valVecsToMerge, constrVecsToMerge, srcDeltaEdges, srcDeltaVals, srcDeltaConstrs, srcoUnUdEdges, srcoUnUdVals, srcoUnUdConstrs, 0);

	return em.getNumNewEdges();
}

/**
 * @param CompSet			-ComputationSet of source vertex
 * @param compsets[] 		-ComputationSet list of in-mem vertices
 * @param intervals[] 		-information about partition intervals
 * @param oldEdgesEmpty		-old edge list is empty
 * @param newEdgesEmpty		-new edge list is empty
 * @param edgeVecsToMerge	-2D vector of sorted edges to merge
 * @param valVecsToMerge	-2D vector of vals associated with edges
 * @param rowMergeID		-current row to add edges to
 * @param context			-grammar checker
 */
void getEdgesToMerge(ComputationSet *compSet, ComputationSet compsets[],
		LoadedVertexInterval intervals[], bool oldEdgesEmpty, bool newEdgesEmpty,
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,
		vector< vector<PseudoPC> > &constrVecsToMerge, int &rowMergeID, Context &context, SEGraph* seg, ExpData &expThreadData, LRUCache &cache_lru)
{
	vector<int> &oldEdges = compSet->getOldEdges();
	vector<char> &oldVals = compSet->getOldVals();
	vector<PseudoPC> &oldConstrs = compSet->getOldConstr();

	vector<int> &newEdges = compSet->getNewEdges();
	vector<char> &newVals = compSet->getNewVals();
	vector<PseudoPC> &newConstrs = compSet->getNewConstr();

	// look through new edges of current vertex to see if any S-Rules
	if (!newEdgesEmpty)
		genS_RuleEdges(newEdges, newVals, newConstrs, edgeVecsToMerge, valVecsToMerge, constrVecsToMerge, rowMergeID, context, seg, expThreadData);

	// look through old edges of current vertex to check if any are in a partition that is currently in memory
	if (!oldEdgesEmpty)
		genD_RuleEdges(compsets, intervals, oldEdges, oldVals, oldConstrs, edgeVecsToMerge, valVecsToMerge, constrVecsToMerge, rowMergeID, context, 'o', seg, expThreadData, cache_lru);

	// look through new edges of current vertex to check if any are in a partition that is currenlty in memory
	if (!newEdgesEmpty)
		genD_RuleEdges(compsets, intervals, newEdges, newVals, newConstrs, edgeVecsToMerge, valVecsToMerge, constrVecsToMerge, rowMergeID, context, 'n', seg, expThreadData, cache_lru);
}

/**
 * For each edge in the outgoing edges list, check if the contextmar for a "S Rules" (single
 * char) rules applies. If so, add it to the new edge list to be merged
 *
 * @param newEdges				-vector of only most recently added edges
 * @param newVals				-vector of values corresponding to new edges
 * @param edgeVecsToMerge		-vector of vectors of edges to merge with source
 * @param valVecsToMerge		-vector of vecotrs of vals to merge with source
 * @param rowMergeID			-current row of vector to add
 * @param context					-grammar checker
 */
void genS_RuleEdges(vector<int> &newEdges, vector<char> &newVals, vector<PseudoPC> &newConstrs,
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,
		vector< vector<PseudoPC> > &constrVecsToMerge, int &rowMergeID, Context &context, SEGraph* seg, ExpData &expThreadData)
{
	char newEdgeVal;
	bool added = false;
	for (int i = 0; i < newEdges.size(); i++) {
		newEdgeVal = context.grammar.checkRules(newVals[i], 0);
		if (newEdgeVal != (char)-1) {
			edgeVecsToMerge[rowMergeID].push_back(newEdges[i]);
			valVecsToMerge[rowMergeID].push_back(newEdgeVal);
			constrVecsToMerge[rowMergeID].push_back(newConstrs[i]);
			added = true;
		}
	}
	// if (added) rowMergeID++;
	if (added) rowMergeID--;
	if (rowMergeID == -1) {
		EdgeMerger_s em_s;
		em_s.mergeVectors(edgeVecsToMerge, valVecsToMerge, constrVecsToMerge);
		rowMergeID++;
	}
}

/**
 * For each outgoing edge of the current source vertex, check if it points to a destination vertex that
 * is currently loaded into memory. If so, check the DESTINATION VERTEX's outgoing edges for D-Rules
 */
void genD_RuleEdges(ComputationSet compsets[], LoadedVertexInterval intervals[], vector<int> &edges,
		vector<char> &vals, vector<PseudoPC> &constrs, vector< vector<int> > &edgeVecsToMerge,
		vector< vector<char> > &valVecsToMerge, vector< vector<PseudoPC> > &constrVecsToMerge,
		int &rowMergeID, Context &context, char flag, SEGraph* seg, ExpData &expThreadData, LRUCache &cache_lru)
{
	int dstInd;
	for (int i = 0; i < edges.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (edges[i] >= intervals[j].getFirstVertex() && edges[i] <= intervals[j].getLastVertex()) {	// if loaded into memory
				dstInd = intervals[j].getIndexStart() + (edges[i] - intervals[j].getFirstVertex());		// calculate offset into ComputationSet
				// if (rowMergeID == edgeVecsToMerge.size()) {				// if current row == size, add a new row
				// 	edgeVecsToMerge.push_back( vector<int>() );
				// 	valVecsToMerge.push_back( vector<char>() );
				// 	constrVecsToMerge.push_back( vector<PseudoPC>() );
				// }
				if (flag == 'o' && compsets[dstInd].getNewEdges().size() > 0)
					checkEdges(dstInd, vals[i], constrs[i], compsets, edgeVecsToMerge, valVecsToMerge, constrVecsToMerge, rowMergeID, context, flag, seg, expThreadData, cache_lru);
				else if (flag == 'n' && compsets[dstInd].getoldUnewEdges().size() > 0)
					checkEdges(dstInd, vals[i], constrs[i], compsets, edgeVecsToMerge, valVecsToMerge, constrVecsToMerge, rowMergeID, context, flag, seg, expThreadData, cache_lru);
			}
		}
	}
}

/**
 * given an index into the ComputationSet list, and the edge value of that vertex, check if any of
 * the outgoing edges fit the context grammar and if so add them to the vector to be merged with the source
 */
void checkEdges(int dstInd, char dstVal, PseudoPC dstConstr, ComputationSet compsets[],
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,
		vector< vector<PseudoPC> > &constrVecsToMerge, int &rowMergeID, Context &context, char flag, SEGraph* seg, ExpData &expThreadData, LRUCache &cache_lru)
{
	vector<int> &edges = (flag == 'o') ? compsets[dstInd].getNewEdges() : compsets[dstInd].getoldUnewEdges();
	vector<char> &vals = (flag == 'o') ? compsets[dstInd].getNewVals() : compsets[dstInd].getoldUnewVals();
	vector<PseudoPC> &constrs = (flag == 'o') ? compsets[dstInd].getNewConstr() : compsets[dstInd].getoldUnewConstr();


	Timer t;
	char newVal;
	bool added = false;
	for (int i = 0; i < edges.size(); i++)
	{
		newVal = context.grammar.checkRules(dstVal, vals[i]);   // check if  ( dstVal  ->  vals[i] ) == newVal
		if (newVal != (char)-1) {
			// t.startTimer();
			PseudoPC newConstr = PseudoPC::combineConstraints(dstConstr, constrs[i]);
			if (newConstr.empty()) {
				expThreadData.numEmptyPPCs++;
				continue;
			}
			string key = newConstr.getConstrRep();
			int8_t f = cache_lru.get(key);
			if (f == -1) {
				t.startTimer();
				RealPC rc = seg->retrieveConstraint(newConstr);
				f = seg->solve(rc);
				t.endTimer();
				expThreadData.constrTime += t.totalTime();
				expThreadData.numSolves++;
				cache_lru.put(key, f);
			} else {
				expThreadData.numCacheHits++;
			}
			if (f == 1) {
			// RealPC rc = seg->retrieveConstraint(newConstr);
			// bool f = seg->solve(rc);
			// expThreadData.numSolves++;
			// t.endTimer();
			// expThreadData.constrTime += t.totalTime();
			// if (f) {
				expThreadData.numTrues++;
				edgeVecsToMerge[rowMergeID].push_back(edges[i]);
				valVecsToMerge[rowMergeID].push_back(newVal);
				constrVecsToMerge[rowMergeID].push_back(newConstr);
				added = true;
			}
		}
	}
	// if (added) rowMergeID++;
	if (added) rowMergeID--;
	if (rowMergeID == -1) {
		EdgeMerger_s em_s;
		em_s.mergeVectors(edgeVecsToMerge, valVecsToMerge, constrVecsToMerge);
		rowMergeID++;
	}
}
