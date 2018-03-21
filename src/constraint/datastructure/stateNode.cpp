#include "stateNode.hpp"

void StateNode::setStateNode(StateNode* &root, list<string> stateNodeList) {
    list<string>::iterator itr = stateNodeList.begin();
    setSatetNode(root, itr);
}

void StateNode::setSatetNode(StateNode* &root, list<string>::iterator &itr) {
    boost::property_tree::ptree pt;
    string str = *itr;
    ++itr;

    stringstream ss(str);
    try{
        boost::property_tree::read_json(ss, pt);
    } catch(boost::property_tree::ptree_error & e) {
        cout<<"Failed to read json"<<endl;
    }
    try{
        boost::property_tree::ptree pt1 = pt.get_child("stateNode");
        if(pt1.empty()){
            root=NULL;
            return;
        }else {
            root = new StateNode();
            //set conditional
            root->conditional = pt1.get<string>("conditional");
            if(root->conditional=="null"){
                root->conditional.clear();
            }
            //set callSites
            boost::property_tree::ptree pt2 = pt1.get_child("callsites");
            if(pt2.empty()){
                root->callsites.clear();
            } else {
                for(BOOST_AUTO(pos, pt2.begin()); pos != pt2.end(); ++pos) {
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
                    boost::property_tree::ptree pt3 = pos->second.get_child("argumentsMap");
                    if(pt3.empty()) {
                        argList.clear();
                    }else {
                        for(BOOST_AUTO(pos3, pt3.begin()); pos3 != pt3.end(); ++pos3) {
                            string str = pos3->second.get_value<string>();
                            argList.push_back(str);
                        }
                    }
                    //retVar
                    string retVar = pos->second.get<string>("retVar");
                    if(retVar == "null") {
                        retVar.clear();
                    }

                    root->callsites.push_back(CallSite(signature, callee, retVar, argList));
                }
            }
            //set returnExp
            root->returnExp = pt1.get<string>("returnExp");
            if(root->returnExp == "null"){
                root->returnExp.clear();
            }
            setSatetNode(root->trueChild, itr);
            setSatetNode(root->falseChild, itr);
            return;
        }

    } catch (boost::property_tree::ptree_error & e) {
        cout<<"Failed to get value: "<<endl;
    }
}
