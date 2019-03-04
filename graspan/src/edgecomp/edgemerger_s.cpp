#include "edgemerger_s.h"

EdgeMerger_s::EdgeMerger_s()
{
	currVID = -1;
}

void EdgeMerger_s::mergeVectors(vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,  vector< vector<PseudoPC> > &constrVecsToMerge)
	{
		MinSet ms1;
		updateMinSet(ms1, edgeVecsToMerge[0], valVecsToMerge[0], constrVecsToMerge[0]);
		MinSet ms2;
		updateMinSet(ms2, edgeVecsToMerge[1], valVecsToMerge[1], constrVecsToMerge[1]);

		vector<int> dstEdges;
		vector<char> dstVals;
		vector<PseudoPC> dstConstrs;

		int max = std::numeric_limits<int>::max();
		while (1)
		{
			if (ms1.getCurrVID() == max && ms2.getCurrVID() == max) {
				break;
			}
			processMinSets(ms1, ms2, edgeVecsToMerge, valVecsToMerge, constrVecsToMerge, dstEdges, dstVals, dstConstrs);
		}

		edgeVecsToMerge[1] = dstEdges;
		valVecsToMerge[1] = dstVals;
		constrVecsToMerge[1] = dstConstrs;

		removeExtraSpace(edgeVecsToMerge[0], valVecsToMerge[0], constrVecsToMerge[0]);
	}

bool EdgeMerger_s::find_val(vector<char> &evals, char val)
{
	return std::find(evals.begin(), evals.end(), val) == evals.end();
}

void EdgeMerger_s::removeExtraSpace(vector<int> &edges, vector<char> &vals, vector<PseudoPC> &constrs)
	{
		edges.clear();
		vals.clear();
		constrs.clear();
	}

void EdgeMerger_s::updateMinSet(MinSet &minset, vector<int> &edges, vector<char> &vals,
	vector<PseudoPC> &constrs)
	{
		minset.setCurrVID(std::numeric_limits<int>::max()); // set the VID as the max so all values will be smaller
		minset.clearEvalSet();

		for (int i = minset.getPtr(); i < edges.size() && edges[i] <= minset.getCurrVID(); i++)
		{
			minset.setCurrVID(edges[i]);
			minset.addEval(vals[i]);
			minset.setPC(constrs[i]);
			minset.incPtr();
		}
	}

void EdgeMerger_s::processMinSets(MinSet &ms1, MinSet &ms2, vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,  vector< vector<PseudoPC> > &constrVecsToMerge, vector<int> &dstEdges, vector<char> &dstVals, vector<PseudoPC> &dstConstrs)
	{
		if (ms1.getCurrVID() > ms2.getCurrVID()) {
			if (currVID != ms2.getCurrVID()) {
				currVID = ms2.getCurrVID();
				currEvals.clear();
			}

			vector<char> &ms2Vals = ms2.getEvals();
			for (vector<char>::iterator iter = ms2Vals.begin(); iter != ms2Vals.end(); iter++)
			{
				if (find_val(currEvals, *iter)) {
					dstEdges.push_back(ms2.getCurrVID());
					dstVals.push_back(*iter);
					dstConstrs.push_back(ms2.getPC());
					currEvals.push_back(*iter);
				}
			}
			updateMinSet(ms2, edgeVecsToMerge[1], valVecsToMerge[1], constrVecsToMerge[1]);
		} else {
			if (currVID != ms1.getCurrVID()) {
				currVID = ms1.getCurrVID();
				currEvals.clear();
			}

			vector<char> &ms1Vals = ms1.getEvals();
			for (vector<char>::iterator iter = ms1Vals.begin(); iter != ms1Vals.end(); iter++)
			{
				if (find_val(currEvals, *iter)) {
					dstEdges.push_back(ms1.getCurrVID());
					dstVals.push_back(*iter);
					dstConstrs.push_back(ms1.getPC());
					currEvals.push_back(*iter);
				}
			}
			updateMinSet(ms1, edgeVecsToMerge[0], valVecsToMerge[0], constrVecsToMerge[0]);
		}
	}
