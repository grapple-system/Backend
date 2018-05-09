#include "seg.hpp"

SEGraph::SEGraph(std::string filename1, string filename2) {
    // TODO: implement SEGraph initialization
    this->constraintMaps = ConstraintMaps(filename1, filename2);
//    std::ifstream input(filename, std::ios::in);
//    if(!input) {
//        cout<<"Failed to open "<<filename<<endl;
//        return;
//    }
//    std::string str;
//    while(getline(input,str)){
//        std::string signature = str;
//        std::list<string> stateNodeList;
//        while(getline(input,str)){
//            //cout<<str<<endl;
//            if(str.size()==0)break;
//            stateNodeList.push_back(str);
//        }
//        this->stateTreeList.push_back(StateTree(signature, stateNodeList));
//        stateNodeList.clear();
//    }
//
//    list<StateTree>::iterator itr = stateTreeList.begin();
//    while(itr!=stateTreeList.end()){
//        (*itr++).print();
//    }
}

RealPC SEGraph::retrieveConstraint(PseudoPC constRep) {
    list<Unit> units = constRep.getUnits();
    string constraint = constraintMaps.getConstraint(units);
    return RealPC(constraint);
}
