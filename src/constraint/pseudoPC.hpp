/*
 * pseudoconstraint.hpp
 *
 *  Created on: Jan 24, 2018
 *      Author: icuzzq
 */

#ifndef CONSTRAINT_PSEUDOPC_HPP_
#define CONSTRAINT_PSEUDOPC_HPP_

#include <string>
#include <list>
#include "datastructure2/unit.hpp"
#include <iostream>
using namespace std;

class PseudoPC
{
    list<Unit> units;

public:
    PseudoPC() {}
    PseudoPC(std::string constr);
    list<Unit> getUnits(){
        return units;
    }
};


#endif /* CONSTRAINT_PSEUDOPC_HPP_ */
