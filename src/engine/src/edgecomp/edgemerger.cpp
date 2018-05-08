#include "edgemerger.h"

// PUBLIC
EdgeMerger::EdgeMerger()
{
	deltaPtr = -1;
	oUnUdPtr = -1;
	currID = -1;
}

/**
* given the vectors and vals to merge, as well as the ID of the source edges,
* merge edges into a new list
*/
void EdgeMerger::mergeVectors(vector< vector<vertexid_t> > &edgeVecsToMerge,
	vector< vector<label_t> > &valVecsToMerge,  vector< vector<PseudoPC> > &constrVecsToMerge,
	vector<vertexid_t> &srcDeltaEdges, vector<label_t> &srcDeltaVals, vector<PseudoPC> &srcDeltaConstrs,
	vector<vertexid_t> &srcoUnUdEdges, vector<label_t> &srcoUnUdVals,
	vector<PseudoPC> &srcoUnUdConstrs, vertexid_t srcID)
	{
		MinSet srcMS;				// initialize a MinSet for the source vertex
		srcMS.setMinSetID(0);
		updateMinSet(srcMS, edgeVecsToMerge[srcID], valVecsToMerge[srcID], constrVecsToMerge[srcID]);		// initialize the info of the source MinSet

		fillPriorityQueue(edgeVecsToMerge, valVecsToMerge, constrVecsToMerge, srcDeltaEdges, srcDeltaVals, srcDeltaConstrs, srcoUnUdEdges, srcoUnUdVals, srcoUnUdConstrs, srcID);

		MinSet tgt;
		int max = std::numeric_limits<int>::max();
		while (1)
		{
			if (!minEdges.empty()) {
				tgt = minEdges.top();		// get reference to the minset with the smallest vertex value
				minEdges.pop();
			}

			if (srcMS.getCurrVID() == max && tgt.getCurrVID() == max) {
				break;
			}

			int indOfTgt = tgt.getMinSetID();
			processMinSets(srcMS, tgt, edgeVecsToMerge[srcID], valVecsToMerge[srcID], constrVecsToMerge[srcID], edgeVecsToMerge[indOfTgt], valVecsToMerge[indOfTgt], constrVecsToMerge[indOfTgt], srcDeltaEdges, srcDeltaVals, srcDeltaConstrs, srcoUnUdEdges, srcoUnUdVals, srcoUnUdConstrs);
		}

		removeExtraSpace(srcDeltaEdges, srcDeltaVals, srcDeltaConstrs, srcoUnUdEdges, srcoUnUdVals, srcoUnUdConstrs);
	}


	// PRIVATE
	/**
	* fill the minEdges priority_queue with the lowest value in each vector. Find the total number of new edges and reserve
	* space in the vectors accordingly
	*/
	void EdgeMerger::fillPriorityQueue(vector< vector<vertexid_t> > &edgeVecsToMerge, vector< vector<label_t> > &valVecsToMerge,
			vector< vector<PseudoPC> > &constrVecsToMerge, vector<vertexid_t> &srcDeltaEdges, vector<label_t> &srcDeltaVals,
			vector<PseudoPC> &srcDeltaConstrs, vector<vertexid_t> &srcoUnUdEdges, vector<label_t> &srcoUnUdVals,
			vector<PseudoPC> &srcoUnUdConstrs, vertexid_t srcID)
		{
			MinSet newminset;
			int totTgtRowSize = 0;
			for (int i = 1; i < edgeVecsToMerge.size(); i++)
			{
				newminset.setMinSetID(i);
				updateMinSet(newminset, edgeVecsToMerge[i], valVecsToMerge[i], constrVecsToMerge[i]);

				totTgtRowSize += edgeVecsToMerge[i].size();
				minEdges.push(newminset);
				newminset.resetPtr();
			}

			srcDeltaEdges.reserve(totTgtRowSize);
			srcDeltaVals.reserve(totTgtRowSize);

			srcoUnUdEdges.reserve(edgeVecsToMerge[srcID].size() + totTgtRowSize);
			srcoUnUdVals.reserve(edgeVecsToMerge[srcID].size() + totTgtRowSize);
		}

		bool EdgeMerger::find_val(vector<label_t> &evals, label_t val)
		{
			return std::find(evals.begin(), evals.end(), val) == evals.end();
		}

		/**
		* remove the excess space created when duplicate values were removed
		*/
		void EdgeMerger::removeExtraSpace(vector<vertexid_t> &srcDeltaEdges, vector<label_t> &srcDeltaVals,
				vector<PseudoPC> &srcDeltaConstrs, vector<vertexid_t> &srcoUnUdEdges,
				vector<label_t> &srcoUnUdVals, vector<PseudoPC> &srcoUnUdConstrs)
		{
			// TODO: this happens no matter what right now. Use a conditional statement to stop this from
			// happening every time and avoid excessive copying!
			srcoUnUdEdges = vector<vertexid_t>(srcoUnUdEdges.begin(), srcoUnUdEdges.begin() + oUnUdPtr + 1);
			srcoUnUdVals = vector<label_t>(srcoUnUdVals.begin(), srcoUnUdVals.begin() + oUnUdPtr + 1);

			srcDeltaEdges = vector<vertexid_t>(srcDeltaEdges.begin(), srcDeltaEdges.begin() + deltaPtr + 1);
			srcDeltaVals = vector<label_t>(srcDeltaVals.begin(), srcDeltaVals.begin() + deltaPtr + 1);
		}

		/**
		* for the given minset, find the next minimum value and any corresponding values
		*/
		void EdgeMerger::updateMinSet(MinSet &minset, vector<vertexid_t> &edges, vector<label_t> &vals,
			vector<PseudoPC> &constrs)
		{
			minset.setCurrVID(std::numeric_limits<int>::max());		// set the VID as the max so all values will be smaller
			minset.clearEvalSet();		// because it is a new vertex, get rid of any values in the edge value set

			for (int i = minset.getPtr(); i < edges.size() && edges[i] <= minset.getCurrVID(); i++)		// find all edge values
			{																							// associated with a
				minset.setCurrVID(edges[i]);															// specific edge value
				minset.addEval(vals[i]);																// and store them in the
				minset.setPC(constrs[i]);																// minset
				minset.incPtr();
			}
		}

		/**
		* compare the next smallest target minset with the source minset to determine which vector to update
		*/
		void EdgeMerger::processMinSets(MinSet &srcMS, MinSet &tgtMS, vector<vertexid_t> &srcEdgesToMerge,
			vector<label_t> &srcValsToMerge, vector<PseudoPC> &srcConstrsToMerge, vector<vertexid_t> &tgtEdgesToMerge,
			vector<label_t> &tgtValsToMerge, vector<PseudoPC> &tgtConstrsToMerge, vector<vertexid_t> &srcDeltaEdges,
			vector<label_t> &srcDeltaVals, vector<PseudoPC> &srcDeltaConstrs, vector<vertexid_t> &srcoUnUdEdges,
			vector<label_t> &srcoUnUdVals, vector<PseudoPC> &srcoUnUdConstrs)
			{
				// case 1 - the target vertexID is smaller than the source vertexID
				if (srcMS.getCurrVID() > tgtMS.getCurrVID()) {
					if (currID != tgtMS.getCurrVID()) {
						currID = tgtMS.getCurrVID();
						currEvals.clear();
					}

					vector<label_t> &tgtVals = tgtMS.getEvals();
					for (vector<label_t>::iterator iter = tgtVals.begin(); iter != tgtVals.end(); iter++)
					{
						if (find_val(currEvals, *iter)) {
							updateVector(tgtMS.getCurrVID(), *iter, tgtMS.getPC(), srcoUnUdEdges, srcoUnUdVals, srcoUnUdConstrs, oUnUdPtr);		// if not add to both oUnUd
							updateVector(tgtMS.getCurrVID(), *iter, tgtMS.getPC(), srcDeltaEdges, srcDeltaVals, srcDeltaConstrs, deltaPtr);		// and Delta
							currEvals.push_back(*iter);				// insert edge value into currEvals to mark as already used
						}
					}
					updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge, tgtConstrsToMerge);
					minEdges.push(tgtMS);

					return;
				}

				// case 2 - target vertexID and source vertexID are equal
				if (srcMS.getCurrVID() == tgtMS.getCurrVID()) {
					if (currID != tgtMS.getCurrVID()) {
						currID = tgtMS.getCurrVID();
						currEvals.clear();
					}

					vector<label_t> &srcVals = srcMS.getEvals();
					vector<label_t> &tgtVals = tgtMS.getEvals();
					for (vector<label_t>::iterator iter = tgtVals.begin(); iter != tgtVals.end(); iter++)
					{
						if (find_val(srcVals, *iter)) {
							if (find_val(currEvals, *iter)) {
								updateVector(tgtMS.getCurrVID(), *iter, tgtMS.getPC(), srcoUnUdEdges, srcoUnUdVals, srcoUnUdConstrs, oUnUdPtr);		// if not add to both oUnUd
								updateVector(tgtMS.getCurrVID(), *iter, tgtMS.getPC(), srcDeltaEdges, srcDeltaVals, srcDeltaConstrs, deltaPtr);		// and Delta
								currEvals.push_back(*iter);
							}
						}
					}
					updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge, tgtConstrsToMerge);
					minEdges.push(tgtMS);

					return;
				}

				// case 3 - source vertexID is less than target vertexID
				if (srcMS.getCurrVID() < tgtMS.getCurrVID()) {
					if (currID != srcMS.getCurrVID()) {
						currID = srcMS.getCurrVID();
						currEvals.clear();
					}

					vector<label_t> &srcVals = srcMS.getEvals();
					for (vector<label_t>::iterator iter = srcVals.begin(); iter != srcVals.end(); iter++)
					{
						if (find_val(currEvals, *iter)) {
							updateVector(srcMS.getCurrVID(), *iter, srcMS.getPC(), srcoUnUdEdges, srcoUnUdVals, srcoUnUdConstrs, oUnUdPtr);		// only add to oUnUd
							currEvals.push_back(*iter);															// because not new
						}
					}
					updateMinSet(srcMS, srcEdgesToMerge, srcValsToMerge, srcConstrsToMerge);
					minEdges.push(tgtMS);

					return;
				}
			}

			/**
			* increment the pointer, then add the vertexID and the edge value into the vector
			*/
			void EdgeMerger::updateVector(vertexid_t vid, label_t val, PseudoPC constr, vector<vertexid_t> &edges, vector<label_t> &vals, vector<PseudoPC> &constrs, int &ptr)
			{
				ptr++;
				edges[ptr] = vid;
				vals[ptr] = val;
				constrs[ptr] = constr;
			}
