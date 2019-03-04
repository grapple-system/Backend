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
    list<int> funcCalls;
    bool isEmpty;

public:
    PseudoPC() {
        this->isEmpty=true;
    }

    // I made this static because I was not sure how else to access this
    // function in the computation. We can discuss this at our meeting
    // Assert pc1.last_pair == pc2.first_pair. In other words, pc1_pc2 is a continuous path.
    // Assert the path exists. Just like func1 call func2, then func2 return to func1 not func3.
    // Otherwise PseudoPC is empty.
    static PseudoPC combineConstraints(PseudoPC pc1, PseudoPC pc2);

    /*
     * generalize this function so that it can serialize more than just the standard string
     * representation.
     * If given a string with multiple units, it currently can't serialize the string
     */
    PseudoPC(string constr);

    PseudoPC(list<Unit> units1, list<Unit> units2, list<int> funcCalls1, list<int> funcCalls2);
    list<Unit> getUnits(){
        return units;
    }

    list<int> getCalls(){
        return funcCalls;
    }

    bool empty(){
        return isEmpty;
    }

    void units_push_back(Unit unit);

    void funcCalls_push_back(int funcId);

    /*
     * serialization function to change the PseudoPC class into a string representation
     *
     * returns a string representing the PseudoPC
     */
    string getConstrRep();
};


#endif /* CONSTRAINT_PSEUDOPC_HPP_ */