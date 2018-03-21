/*
 * seg.hpp
 *
 *  Created on: Jan 24, 2018
 *      Author: icuzzq
 */

#ifndef CONSTRAINT_SEG_HPP_
#define CONSTRAINT_SEG_HPP_

#include <fstream>
#include <iostream>
using namespace std;

#include "realPC.hpp"
#include "pseudoPC.hpp"
#include "datastructure/stateTree.hpp"

class SEGraph {
private:
  std::list<StateTree> stateTreeList;
  RealPC retrieveConstraint(PseudoPC constRep);

public:
  SEGraph() {}
  SEGraph(std::string filename);

  bool solve(RealPC pathConst);  // place holder for constraint solver
};


#endif /* CONSTRAINT_SEG_HPP_ */
