/**
 * Created by wangyifei on 2018/4/2.
 */

#ifndef STATEMAPS_HPP_
#define STATEMAPS_HPP_

#include "unit.hpp"
#include "constraintNode.hpp"

class ConstraintMaps{
private:
    // map<signature, map<NodeIndex, constraintNode>
    map<string, map<int, ConstraintNode>> constraintMaps;

public:
    ConstraintMaps() {}
    ConstraintMaps(string filename);
    string getConstraint(Unit unit);
    string getConstraint(list<Unit> units);
    void setConstraint(map<int, ConstraintNode> &constraintMap, int i, list<string>::iterator &itr);
    void print();
};

#endif