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
    set<string> const_int;
    set<string> const_real;
    set<string> const_bvec;
    set<string> const_bool;
    set<string> assert_cons;

    //type: "$I"|"$D"
    void genConst_set(string constraint);
public:
    RealPC() {}
    RealPC(string constraint);
    set<string> getConst_int(){
        return const_int;
    }
    set<string> getConst_real(){
        return const_real;
    }
    set<string> getConst_bvec(){
        return const_bvec;
    }
    set<string> getAssert_cons(){
        return assert_cons;
    }
};


#endif /* CONSTRAINT_REALPC_HPP_ */