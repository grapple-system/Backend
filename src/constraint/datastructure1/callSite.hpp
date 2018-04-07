/**
 * Created by wangyifei on 2018/3/20.
 */

#ifndef CALLSITE_HPP_
#define CALLSITE_HPP_

#include <string>
#include <list>
#include <map>
#include <iostream>
using namespace std;

class CallSite {
private:
    string signature;
    string callee;
    map<string,string> argumentsMap;
    string retVar;
public:
    CallSite() {}
    CallSite(string signature, string callee, string retVar, list<string> argList);
    void print(){
        cout<<"\tCallSite:"<<endl;
        cout<<"\t\tsignature: "<<signature<<endl;
        cout<<"\t\tcallee: "<<callee<<endl;
        cout<<"\t\tretVar: "<<retVar<<endl;
        cout<<"\t\targumentsMap:"<<endl;
        map<string, string>::iterator itr = argumentsMap.begin();
        while(itr!=argumentsMap.end()){
            cout<<"\t\t\t"<<(*itr).first<<" = "<<(*itr).second<<endl;
            itr++;
        }
    }

};

#endif