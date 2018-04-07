/**
 * Created by wangyifei on 2018/3/20.
 */

#ifndef STATENODE_HPP_
#define STATENODE_HPP_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/typeof/typeof.hpp>

#include "callSite.hpp"

class StateNode {
private:
    string conditional;
    list<CallSite> callsites;
    string returnExp;

    StateNode* trueChild;
    StateNode* falseChild;
public:
    StateNode() {
        this-> trueChild = NULL;
        this-> falseChild = NULL;
    }
    void setStateNode(StateNode* &root, list<string> stateNodeList);
    void setStateNode(StateNode* &root, list<string>::iterator &itr);
//    void setConditional(string conditional) {
//        this->conditional = conditional;
//    }
//    void setReturnExpr(string returnExpr) {
//        this->returnExpr = returnExpr;
//    }
    void print(StateNode* root){
        if(root == NULL){
            cout<<"null"<<endl;
            return;
        }
        cout<<"stateNode:"<<endl;
        cout<<"\tconditional: "<<root->conditional<<endl;
        cout<<"\treturnExp: "<<root->returnExp<<endl;
        list<CallSite>::iterator itr = root->callsites.begin();
        while(itr!=root->callsites.end()){
            (*itr++).print();
        }
        print(root->trueChild);
        print(root->falseChild);
    }

};

#endif