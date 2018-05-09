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

class SEGraph {

public:
  SEGraph() {}
  SEGraph(std::string filename);

  RealPC retrieveConstraint(PseudoPC constRep);

  bool solve(RealPC rc1, RealPC rc2);  // place holder for constraint solver

};


#endif /* CONSTRAINT_SEG_HPP_ */
