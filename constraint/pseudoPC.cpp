#include "pseudoPC.hpp"

PseudoPC::PseudoPC(string constr) {
    // constr must be like "[(left1,left2),(right1,right2)]"
    // TODO: generalize implementation for strings of arbitray size (any number of units)
    int len = constr.length();
    this->isEmpty = false;
    if(len<=9)return;
    int unit_left = constr.find("[");
    int unit_len = constr.find("]",unit_left);
    while(unit_len!=-1) {
        string unit_str = constr.substr(unit_left,unit_len);
        int split1 = unit_str.find(",");
        int split2 = unit_str.find(",", split1 + 1);
        int split3 = unit_str.find(",", split2 + 1);
        long left1 = atol(unit_str.substr(2, split1).c_str());
        long left2 = atol(unit_str.substr(split1 + 1, split2 - 1).c_str());
        long right1 = atol(unit_str.substr(split2 + 2, split3).c_str());
        long right2 = atol(unit_str.substr(split3 + 1, unit_str.size() - 2).c_str());

        if(left1!=right1){
            if(right2==0) {
                this->funcCalls.push_back(right1);
            }else if(this->funcCalls.empty()||this->funcCalls.back()<0){
                this->funcCalls.push_back(-left1-1);
            }else if(this->funcCalls.back()>0&&this->funcCalls.back()==left1){
                this->funcCalls.pop_back();
            }else{
                this->units.clear();
                this->isEmpty=true;
                return;
            }
        }
        this->units_push_back(Unit(left1, left2, right1, right2));
        //if (left1 != right1) this->funcCalls.push(right1);
        //cout << left1 << " " << left2 << " " << right1 << " " << right2 << endl;
        unit_left = constr.find("[",unit_left+1);
        unit_len = constr.find("]",unit_left);
    }
}

PseudoPC::PseudoPC(list<Unit> units1, list<Unit> units2, list<int> funcCalls1, list<int> funcCalls2){
    this->isEmpty = false;
    list<Unit>::iterator ite =units1.begin();
    while(ite!=units1.end()){
        this->units_push_back(*ite);
        ++ite;
    }
    ite = units2.begin();
    while(ite!=units2.end()){
        this->units_push_back(*ite);
        ++ite;
    }

    list<int>::iterator ite_f = funcCalls1.begin();
    while(ite_f!=funcCalls1.end()){
        this->funcCalls_push_back(*ite_f);
        ++ite_f;
    }
    ite_f = funcCalls2.begin();
    while(ite_f!=funcCalls2.end()){
        this->funcCalls_push_back(*ite_f);
        ++ite_f;
    }
}

PseudoPC PseudoPC::combineConstraints(PseudoPC pc1, PseudoPC pc2) {
    // TODO: combine PseudoPCs here and return a new PseudoPC
    // Assert pc1.last_pair == pc2.first_pair. In other words, pc1_pc2 is a continuous path.
    // Assert the path exists. Just like func1 call func2, then func2 return to func1 not func3.
    if(pc1.getUnits().empty())return pc2;
    if(pc2.getUnits().empty())return pc1;

    pair<long, long> pc1_last_pair = pc1.getUnits().back().getPair2();
    pair<long, long> pc2_first_pair = pc2.getUnits().front().getPair1();
    if(pc1_last_pair!=pc2_first_pair)return PseudoPC();

    list<int> funcCalls1 = pc1.getCalls();
    list<int> funcCalls2 = pc2.getCalls();
    while(true){
        if(funcCalls1.empty()||funcCalls2.empty())break;
        if(funcCalls1.back()>=0&&funcCalls2.front()<0){
            if(-funcCalls1.back()-1==funcCalls2.front()){
                funcCalls1.pop_back();
                funcCalls2.pop_front();
            }else{
                return PseudoPC();
            }
        }else break;
    }

    return PseudoPC(pc1.getUnits(), pc2.getUnits(), funcCalls1, funcCalls2);
}

void PseudoPC::units_push_back(Unit unit){
    if(this->units.size()==0){
        this->units.push_back(unit);
        return;
    }

    Unit back = this->units.back();
    if(back.getPair1().first==back.getPair2().first&&unit.getPair1().first==unit.getPair2().first&&back.getPair2()==unit.getPair1()){
        this->units.back().setPair2(unit.getPair2());
    }else{
        this->units.push_back(unit);
    }
    return;
}

void PseudoPC::funcCalls_push_back(int funcId){
    this->funcCalls.push_back(funcId);
    return;
}

string PseudoPC::getConstrRep() {
  // TODO: fix this implementation for PseudoPCs of arbitrary size
    list<Unit>::iterator ite =this->units.begin();
    string ret = "";
    while(ite!=units.end()){
        ret = ret + ite->toString();
        ++ite;
    }
    return ret;
}