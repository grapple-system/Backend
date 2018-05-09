#include "seg.hpp"

SEGraph::SEGraph(std::string filename1, string filename2) {
    // TODO: implement SEGraph initialization
    this->constraintMaps = ConstraintMaps(filename1, filename2);
}

RealPC SEGraph::retrieveConstraint(PseudoPC constRep) {
    list<Unit> units = constRep.getUnits();
    string constraint = constraintMaps.getConstraint(units);
    return RealPC(constraint);
}
