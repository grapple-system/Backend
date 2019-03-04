/**
 * Created by wangyifei on 2018/4/2.
 */

#include "constraintMaps.hpp"

ConstraintMaps::ConstraintMaps(string filepath) {
    ifstream input(filepath);
    if(!input) {
        cout<<"Failed to open "<<filepath<<endl;
        return;
    }
    string str;
    while(getline(input,str)){
        int split =str.find_first_of(":");
        string keyString=str.substr(0, split);
        string constraintString = str.substr(split+1);
        //cout<<keyString<<" "<<constraintString<<endl;
        constraintMaps[keyString]=constraintString;
    }
}

string ConstraintMaps::getConstraint(Unit unit) {
    //unit:[pair1,pair2]
    //pair1:(first1,second1)
    //pair2:(first2,second2)
    string ret = "";
    long first1 = unit.getPair1().first;
    long second1 = unit.getPair1().second;
    long first2 = unit.getPair2().first;
    long second2 = unit.getPair2().second;
    if(second1<0||second2<0)return ret;
    if(first1==first2&&second1>second2&&second2!=0)return ret;
    if(first1==first2){
        long t1 = second2/2;
        long t2 = second2;
        while(second1 != t2){
            string key = Unit::pairToString(first1,t1);
            string constraint = constraintMaps[key];
            if(constraint.size()!=0){
                if(t2 == t1*2+1){
                    //ret = ret + "#"+constraint;
                    ret.append("#");
                    ret.append(constraint);
                } else{
                    //ret = ret + "#(not "+constraint+")";
                    ret.append("#(not ");
                    ret.append(constraint);
                    ret.append(")");
                }
            }
            t2 = t1;
            t1 = t1/2;
        }
    }else{
        string constraint = constraintMaps[unit.toString()];
        if(constraint.size()>0){
            ret.append("#");
            ret.append(constraint);
        }
    }
    return ret;
}

string ConstraintMaps::getConstraint(list<Unit> units) {
    if(units.empty())return "";
    list<Unit>::iterator itr = units.begin();
    string ret = getConstraint(*itr);
    ++itr;
    while(itr != units.end()){
        string str = getConstraint(*itr);
        if(str.size()!=0){
            ret.append(str);
        }
        ++itr;
    }
    return ret;
}
void ConstraintMaps::print() {
    map<string,string>::iterator ite = constraintMaps.begin();
    while(ite != constraintMaps.end()){
        cout<<ite->first<<":"<<constraintMaps[ite->first]<<endl;
        ++ite;
    }

}
