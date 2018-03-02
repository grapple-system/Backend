#include "vertex.h"

// Constructors
Vertex::Vertex(vertexid_t id, vector<vertexid_t> outEdges, vector<label_t> outEdgeValues, vector<PseudoPC> constraints, vector<string> tempstrs)
{
	this->id = id;
	this->outEdges = outEdges;
	this->outEdgeValues = outEdgeValues;
	this->constraints = constraints;
	this->temp = tempstrs;

	numOutEdges = outEdges.size();
}


/**
 * Description: display a vertex as its id and the destination vertices it points to
 * with their grammar
 *
 * @return string output
 */
string Vertex::toString()
{
	std::stringstream output;

	output << endl << id << " ->  ";
	for (int i = 0; i < numOutEdges; i++)
		output << "(" << outEdges[i] << ", " << (short)(outEdgeValues[i]) << ")  ";


	return output.str();
}
