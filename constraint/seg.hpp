/*
 * seg.hpp
 *
 *  Created on: Jan 24, 2018
 *      Author: icuzzq
 */

#ifndef CONSTRAINT_SEG_HPP_
#define CONSTRAINT_SEG_HPP_

#include "realPC.hpp"
#include "pseudoPC.hpp"
#include "datastructures/constraintMaps.hpp"

class SEGraph {

private:
    ConstraintMaps constraintMaps;

public:
    SEGraph() {}

    // Update SEGraph()
    // filepath is path of "interSmt2"
    SEGraph(string filepath);
    RealPC retrieveConstraint(PseudoPC constRep);

    bool solve(RealPC pathConst);  // place holder for constraint solver

};


#endif /* CONSTRAINT_SEG_HPP_ */
