/*
 * pseudoconstraint.hpp
 *
 *  Created on: Jan 24, 2018
 *      Author: icuzzq
 */

#ifndef CONSTRAINT_PSEUDOPC_HPP_
#define CONSTRAINT_PSEUDOPC_HPP_

#include "datastructures/unit.hpp"


class PseudoPC
{
    list<Unit> units;

public:
    PseudoPC() {}
    PseudoPC(string constr);
    list<Unit> getUnits(){
        return units;
    }
};


#endif /* CONSTRAINT_PSEUDOPC_HPP_ */
