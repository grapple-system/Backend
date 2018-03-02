#ifndef COMPUTATIONSET_H
#define COMPUTATIONSET_H

#include "../utilities/globalDefinitions.hpp"

class ComputationSet
{
	vector<vertexid_t> oldEdges;		// edges from last iter
	vector<label_t> oldVals;
	vector<PseudoPC> oldConstr;

	vector<vertexid_t> newEdges;		// edges from most recent iter
	vector<label_t> newVals;
	vector<PseudoPC> newConstr;

	vector<vertexid_t> oldUnewEdges;	// all edges up to prev iter
	vector<label_t> oldUnewVals;
	vector<PseudoPC> oldUnewConstr;

	// VECTORS WILL STORE NEW EDGES UNTIL END OF COMPUTATION
	vector<vertexid_t> deltaEdges;		// new edges to be added this iter
	vector<label_t> deltaVals;
	vector<PseudoPC> deltaConstr;

	vector<vertexid_t> oUnUdEdges;		// all edges inlcuding new
	vector<label_t> oUnUdVals;
	vector<PseudoPC> oUnUdConstr;


	public:
	// Constructor
	ComputationSet() {}

	// old getters and setters
	inline vector<vertexid_t> &getOldEdges() { return oldEdges; }
	inline vector<label_t> &getOldVals() { return oldVals; }
	inline vector<PseudoPC> &getOldConstr() { return oldConstr; }

	inline void setOldEdges(vector<vertexid_t> &oldEdges) { this->oldEdges = oldEdges; }
	inline void setOldVals(vector<label_t> &oldVals) { this->oldVals = oldVals; }
	inline void setOldConstr(vector<PseudoPC> &oldConstr) { this->oldConstr = oldConstr; }

	 // new getters and setters
	inline vector<vertexid_t> &getNewEdges() { return newEdges; }
	inline vector<label_t> &getNewVals() { return newVals; }
	inline vector<PseudoPC> &getNewConstr() { return newConstr; }

	inline void setNewEdges(vector<vertexid_t> &newEdges) { this->newEdges = newEdges; }
	inline void setNewVals(vector<label_t> &newVals) { this->newVals = newVals; }
	inline void setNewConstr(vector<PseudoPC> &newConstr) { this->newConstr = newConstr; }

	// old U new getters and setters
	inline vector<vertexid_t> &getoldUnewEdges() { return oldUnewEdges; }
	inline vector<label_t> &getoldUnewVals() { return oldUnewVals; }
	inline vector<PseudoPC> &getoldUnewConstr() { return oldUnewConstr; }

	inline void setoldUnewEdges(vector<vertexid_t> &oldUnewEdges) { this->oldUnewEdges = oldUnewEdges; }
	inline void setoldUnewVals(vector<label_t> &oldUnewVals) { this->oldUnewVals = oldUnewVals; }
	inline void setoldUnewConstr(vector<PseudoPC> &oldUnewConstr) { this->oldUnewConstr = oldUnewConstr; }


	/*
		In order to ensure all edges are added, any edges added in the current iteration are
		stored in the delta vectros so the state of the graph does not change until all edges
		have been added for every vertex
	*/
	// delta getters and setters
	inline vector<vertexid_t> &getDeltaEdges() { return deltaEdges; }
	inline vector<label_t> &getDeltaVals() { return deltaVals; }
	inline vector<PseudoPC> &getDeltaConstr() { return deltaConstr; }

	inline void setDeltaEdges(vector<vertexid_t> &deltaEdges) { this->deltaEdges = deltaEdges; }
	inline void setDeltaVals(vector<label_t> &deltaVals) { this->deltaVals = deltaVals; }
	inline void setDeltaConstr(vector<PseudoPC> &deltaConstr) { this->deltaConstr = deltaConstr; }

	// old U new U delta getters and setters
	inline vector<vertexid_t> &getoUnUdEdges() { return oUnUdEdges; }
	inline vector<label_t> &getoUnUdVals() { return oUnUdVals; }
	inline vector<PseudoPC> &getoUnUdConstr() { return oUnUdConstr; }

	inline void setoUnUdEdges(vector<vertexid_t> &oUnUdEdges) { this->oUnUdEdges = oUnUdEdges; }
	inline void setoUnUdVals(vector<label_t> &oUnUdVals) { this->oUnUdVals = oUnUdVals; }
	inline void setoUnUdConstr(vector<PseudoPC> &oUnUdConstr) { this->oUnUdConstr = oUnUdConstr; }
};

#endif
