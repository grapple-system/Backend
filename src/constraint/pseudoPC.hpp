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


class PseudoPC
{

public:
    PseudoPC() {}
    PseudoPC(std::string constr);

    static PseudoPC combineConstraints(PseudoPC c1, PseudoPC c2);
};


#endif /* CONSTRAINT_PSEUDOPC_HPP_ */
