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
    List<int> constrRep;        // using int as a temporary filler

public:
    PseudoPC() {}
    PseudoPC(std::string constr);
};


#endif /* CONSTRAINT_PSEUDOPC_HPP_ */
