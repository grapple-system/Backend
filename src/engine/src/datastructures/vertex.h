#ifndef VERTEX_H
#define VERTEX_H

#include <sstream>
#include "../utilities/globalDefinitions.hpp"

/**
 * PSA includes
 */
#include "../../../constraint/pseudoPC.hpp"

class Vertex
{
	vertexid_t id;
	int numOutEdges;		// degree

	vector<vertexid_t> outEdges;
	vector<label_t> outEdgeValues;
	vector<PseudoPC> constraints;

	vector<string> temp;


	public:
	// Constructors
	Vertex() { numOutEdges = 0; }
	Vertex(int id, int outDegree);
	Vertex(vertexid_t id, vector<vertexid_t> outEdges, vector<label_t> outEdgeValues, vector<PseudoPC> constraints);

	// Getters
	inline int getVertexID() { return id; }
	inline int getNumOutEdges() { return numOutEdges; }
	inline vector<vertexid_t> &getOutEdges() { return outEdges; }
	inline vector<label_t> &getOutEdgeValues() { return outEdgeValues; }
	inline vector<PseudoPC> &getConstrs() { return constraints; }

	inline vector<string> &getTemp() { return temp; }

	inline vertexid_t getOutEdge(vertexid_t ind) { return outEdges[ind]; }
	inline label_t getOutEdgeValue(vertexid_t ind) { return outEdgeValues[ind]; }
	inline PseudoPC getConstr(vertexid_t ind) { return constraints[ind]; }
	inline string getTempStr(vertexid_t ind) { return temp[ind]; }

	// Setters
	inline void setNumOutEdges(int numEdges) { this->numOutEdges = numEdges; }
	inline void setOutEdges(vector<vertexid_t> &outEdges) { this->outEdges = outEdges; }
	inline void setOutEdgeValues(vector<label_t> &outEdgeValues) { this->outEdgeValues = outEdgeValues; }
	inline void setConstraints(vector<PseudoPC> &constraints) { this->constraints = constraints; }
	inline void setTempStr(vector<string> &tempStrs) { this->temp = tempStrs; }

	// clean up memory from vertices
	inline void clearVector() {
		outEdges.clear();
		outEdgeValues.clear();
		constraints.clear();

		vector<vertexid_t>().swap(outEdges);
		vector<label_t>().swap(outEdgeValues);
		vector<PseudoPC>().swap(constraints);
		numOutEdges = 0;
	};

	string toString();
};


#endif
