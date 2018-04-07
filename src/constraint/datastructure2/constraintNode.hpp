/**
 * Created by wangyifei on 2018/4/7.
 */
#ifndef CONSTRAINTNODE_HPP_
#define CONSTRAINTNODE_HPP_

#include <map>
#include <list>
#include <fstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/typeof/typeof.hpp>
using namespace std;

class ConstraintNode {
private:
    string conditional;
    string returnExp;
    class CallSite {
    private:
        string signature;
        string callee;
        map<string,string> argumentsMap;
        string retVar;
    public:
        CallSite() {}
        CallSite(string signature, string callee, string retVar, list<string> argList){
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
    };
    list<CallSite> callsites;
public:
    ConstraintNode(){};
    ConstraintNode(boost::property_tree::ptree pt);
    string getConditional(){
        return conditional;
    }
};

#endif
