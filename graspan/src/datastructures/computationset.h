#ifndef COMPUTATIONSET_H
#define COMPUTATIONSET_H

#include "../utilities/globalDefinitions.hpp"

class ComputationSet
{
	vector<int> oldEdges;		// edges from last iter
	vector<char> oldVals;
	vector<PseudoPC> oldConstr;

	vector<int> newEdges;		// edges from most recent iter
	vector<char> newVals;
	vector<PseudoPC> newConstr;

	vector<int> oldUnewEdges;	// all edges up to prev iter
	vector<char> oldUnewVals;
	vector<PseudoPC> oldUnewConstr;

	// VECTORS WILL STORE NEW EDGES UNTIL END OF COMPUTATION
	vector<int> deltaEdges;		// new edges to be added this iter
	vector<char> deltaVals;
	vector<PseudoPC> deltaConstr;

	vector<int> oUnUdEdges;		// all edges inlcuding new
	vector<char> oUnUdVals;
	vector<PseudoPC> oUnUdConstr;


	public:
	// Constructor
	ComputationSet() {}

	// old getters and setters
	inline vector<int> &getOldEdges() { return oldEdges; }
	inline vector<char> &getOldVals() { return oldVals; }
	inline vector<PseudoPC> &getOldConstr() { return oldConstr; }

	inline void setOldEdges(vector<int> &oldEdges) { this->oldEdges = oldEdges; }
	inline void setOldVals(vector<char> &oldVals) { this->oldVals = oldVals; }
	inline void setOldConstr(vector<PseudoPC> &oldConstr) { this->oldConstr = oldConstr; }
	 
	 // new getters and setters
	inline vector<int> &getNewEdges() { return newEdges; }
	inline vector<char> &getNewVals() { return newVals; }
	inline vector<PseudoPC> &getNewConstr() { return newConstr; }

	inline void setNewEdges(vector<int> &newEdges) { this->newEdges = newEdges; }
	inline void setNewVals(vector<char> &newVals) { this->newVals = newVals; }
	inline void setNewConstr(vector<PseudoPC> &newConstr) { this->newConstr = newConstr; }

	// old U new getters and setters
	inline vector<int> &getoldUnewEdges() { return oldUnewEdges; }
	inline vector<char> &getoldUnewVals() { return oldUnewVals; }
	inline vector<PseudoPC> &getoldUnewConstr() { return oldUnewConstr; }

	inline void setoldUnewEdges(vector<int> &oldUnewEdges) { this->oldUnewEdges = oldUnewEdges; }
	inline void setoldUnewVals(vector<char> &oldUnewVals) { this->oldUnewVals = oldUnewVals; }
	inline void setoldUnewConstr(vector<PseudoPC> &oldUnewConstr) { this->oldUnewConstr = oldUnewConstr; }


	/*
		In order to ensure all edges are added, any edges added in the current iteration are
		stored in the delta vectros so the state of the graph does not change until all edges
		have been added for every vertex
	*/
	// delta getters and setters
	inline vector<int> &getDeltaEdges() { return deltaEdges; }
	inline vector<char> &getDeltaVals() { return deltaVals; }
	inline vector<PseudoPC> &getDeltaConstr() { return deltaConstr; }

	inline void setDeltaEdges(vector<int> &deltaEdges) { this->deltaEdges = deltaEdges; }
	inline void setDeltaVals(vector<char> &deltaVals) { this->deltaVals = deltaVals; }
	inline void setDeltaConstr(vector<PseudoPC> &deltaConstr) { this->deltaConstr = deltaConstr; }

	// old U new U delta getters and setters
	inline vector<int> &getoUnUdEdges() { return oUnUdEdges; }
	inline vector<char> &getoUnUdVals() { return oUnUdVals; }
	inline vector<PseudoPC> &getoUnUdConstr() { return oUnUdConstr; }

	inline void setoUnUdEdges(vector<int> &oUnUdEdges) { this->oUnUdEdges = oUnUdEdges; }
	inline void setoUnUdVals(vector<char> &oUnUdVals) { this->oUnUdVals = oUnUdVals; }
	inline void setoUnUdConstr(vector<PseudoPC> &oUnUdConstr) { this->oUnUdConstr = oUnUdConstr; }
};

#endif
