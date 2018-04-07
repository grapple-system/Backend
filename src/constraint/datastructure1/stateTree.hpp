/**
 * Created by wangyifei on 2018/3/20.
 */

#ifndef STATETREE_HPP_
#define STATETREE_HPP_

#include "stateNode.hpp"

class StateTree {
private:
    string signature;
    StateNode* root;
public:
    StateTree() {
        this->root = NULL;
    }
    StateTree(string signature, list<string> stateNodeList);

    string getSignature(){
        return signature;
    }
    void print(){
        cout<<signature<<endl;
        if(root != NULL)root->print(root);
        cout<<endl;
    }
};

#endif