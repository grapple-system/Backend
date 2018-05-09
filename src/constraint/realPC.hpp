/*
 * realconstraint.hpp
 *
 *  Created on: Jan 24, 2018
 *      Author: icuzzq
 */

#ifndef CONSTRAINT_REALPC_HPP_
#define CONSTRAINT_REALPC_HPP_
#include <string>

class RealPC {
private:
    std::string constraint;
public:
    RealPC() {}
    RealPC(std::string constraint){
        this->constraint = constraint;
    }
    std::string getConstraint(){
        return constraint;
    }
};


#endif /* CONSTRAINT_REALPC_HPP_ */
