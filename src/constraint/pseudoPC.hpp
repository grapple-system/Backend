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

    PseudoPC(PseudoPC c1, PseudoPC c2);   // create PseudoPC that is
                                                    // combination fo two others
};


#endif /* CONSTRAINT_PSEUDOPC_HPP_ */
