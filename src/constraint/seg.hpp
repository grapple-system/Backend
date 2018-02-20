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
private:
  RealPC retrieveConstraint(PseudoPC constRep);

public:
  SEGraph() {}

  boolean solve(RealPC pathConst);  // place holder for constraint solver
};


#endif /* CONSTRAINT_SEG_HPP_ */
