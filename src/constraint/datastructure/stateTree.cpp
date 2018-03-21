/**
 * Created by wangyifei on 2018/3/20.
 */

#include "stateTree.hpp"

StateTree::StateTree(string signature, list<string> stateNodeList) {
    this->signature = signature;
    root->setStateNode(root,stateNodeList);
}
