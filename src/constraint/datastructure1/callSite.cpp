#include "callSite.hpp"
CallSite::CallSite(string signature, string callee, string retVar, list<string> argList) {
    this->signature = signature;
    this->callee = callee;
    this->retVar =retVar;
    list<string>::iterator itr = argList.begin();
    while(itr!=argList.end()){
        string temp = *itr;
        int i = temp.find(" = ");
        string key = temp.substr(0, i);
        string value = temp.substr(i+3, temp.length());
        this->argumentsMap[key]=value;
        itr++;
    }
}