/**
 * Created by wangyifei on 2018/4/7.
 */

#include "constraintNode.hpp"

ConstraintNode::ConstraintNode(ptree pt) {
    try{
        //set conditional
        this->conditional = pt.get<string>("conditional");
        if(this->conditional=="null"){
            this->conditional.clear();
        }
        //set callSites
        ptree pt1 = pt.get_child("callsites");
        if(pt1.empty()){
            this->callsites.clear();
        } else {
            for(BOOST_AUTO(pos, pt1.begin()); pos != pt1.end(); ++pos) {
                //siganture
                string signature = pos->second.get<string>("signature");
                if(signature == "null") {
                    signature.clear();
                }
                //callee
                string callee = pos->second.get<string>("callee");
                if(callee == "null") {
                    callee.clear();
                }
                //argumentsMap
                list<string> argList;
                ptree pt2 = pos->second.get_child("argumentsMap");
                if(pt2.empty()) {
                    argList.clear();
                }else {
                    for(BOOST_AUTO(pos2, pt2.begin()); pos2 != pt2.end(); ++pos2) {
                        string str = pos2->second.get_value<string>();
                        argList.push_back(str);
                    }
                }
                //retVar
                string retVar = pos->second.get<string>("retVar");
                if(retVar == "null") {
                    retVar.clear();
                }

                this->callsites.push_back(CallSite(signature, callee, retVar, argList));
            }
        }
        //set returnExp
        this->returnExp = pt.get<string>("returnExp");
        if(this->returnExp == "null"){
            this->returnExp.clear();
        }
        return;

    } catch (ptree_error & e) {
        cout<<"Failed to get value: "<<endl;
    }
}