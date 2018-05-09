/*
 * realconstraint.hpp
 *
 *  Created on: Jan 24, 2018
 *      Author: icuzzq
 */

#ifndef CONSTRAINT_REALPC_HPP_
#define CONSTRAINT_REALPC_HPP_

#include "common.hpp"

class RealPC {
private:
    string constraint;
public:
    RealPC() {}
    RealPC(string constraint){
        this->constraint = constraint;
    }
    string getConstraint(){
        return constraint;
    }
};


#endif /* CONSTRAINT_REALPC_HPP_ */
