#ifndef VERTEX_H
#define VERTEX_H

#include <sstream>
#include "../utilities/globalDefinitions.hpp"

#include "../../../constraint/pseudoPC.hpp"

class Vertex
{
	vertexid_t id;
	int numOutEdges;		// degree

	vector<vertexid_t> outEdges;	
	vector<label_t> outEdgeValues;

	vector<string> temp;
	vector<PseudoPC> constraints;

	public:
	// Constructors
	Vertex() { numOutEdges = 0; }
	Vertex(int id, int outDegree);
	Vertex(int id, vector<int> outEdges, vector<char> outEdgeValues);
	Vertex(int id, vector<int> outEdges, vector<char> outEdgeValues, vector<PseudoPC> constraints);

	// Getters
	inline int getVertexID() { return id; }
	inline int getNumOutEdges() { return numOutEdges; }
	inline vector<int> &getOutEdges() { return outEdges; }
	inline vector<char> &getOutEdgeValues() { return outEdgeValues; }

	inline vector<string> &getTemp() { return temp; }
	inline vector<PseudoPC> &getConstrs() { return constraints; }

	inline int getOutEdge(int ind) { return outEdges[ind]; }
	inline char getOutEdgeValue(int ind) { return outEdgeValues[ind]; }
	inline PseudoPC getConstr(int ind) { return constraints[ind]; }

	// Setters
	inline void setNumOutEdges(int numEdges) { this->numOutEdges = numEdges; }
	inline void setOutEdges(vector<int> &outEdges) { this->outEdges = outEdges; }
	inline void setOutEdgeValues(vector<char> &outEdgeValues) { this->outEdgeValues = outEdgeValues; }
	inline void setConstraints(vector<PseudoPC> &constraints) { this->constraints = constraints; }

	// clean up memory from vertices
	inline void clearVector() { 
		outEdges.clear();
		outEdgeValues.clear();
		temp.clear();
		constraints.clear();
		
		vector<vertexid_t>().swap(outEdges);
		vector<label_t>().swap(outEdgeValues);
		vector<string>().swap(temp);
		vector<PseudoPC>().swap(constraints);
		numOutEdges = 0;
	};
	
	string toString();
};


#endif
