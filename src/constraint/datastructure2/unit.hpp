/**
 * Created by wangyifei on 2018/4/2.
 */

#ifndef UNIT_HPP_
#define UNIT_HPP_

#include <string>
using  namespace std;

class Unit {
private:
    string signature;
    int start;
    int end;
public:
    Unit(string signature, int start, int end){
        this->signature = signature;
        this->start = start;
        this->end = end;
    }

    string getSignature(){
        return signature;
    }

    int getStart(){
        return start;
    }

    int getEnd(){
        return end;
    }

    void setEnd(int end){
        this->end = end;
    }
};

#endif