/**
 * Created by wangyifei on 2018/4/2.
 */

#ifndef UNIT_HPP_
#define UNIT_HPP_

#include "../common.hpp"


class Unit {
private:
    pair<long, long> pair1,pair2;
public:
    //(left1, left2), (right1, right2)
    Unit(long left1, long left2, long right1, long right2){
        this->pair1.first = left1;
        this->pair1.second = left2;
        this->pair2.first = right1;
        this->pair2.second = right2;
    }

    pair<long, long> getPair1(){
        return pair1;
    }

    pair<long, long> getPair2(){
        return pair2;
    }

    string toString(){
        stringstream ss;
        ss<<"[("<<pair1.first<<","<<pair1.second<<"),("<<pair2.first<<","<<pair2.second<<")]";
        string str;
        ss>>str;
        return str;
    }

    string static pairToString(long first, long second){
        stringstream ss;
        ss<<"("<<first<<","<<second<<")";
        string str;
        ss>>str;
        return str;

    }

    void setPair2(pair<long,long> pair2){
        this->pair2=pair2;
    }
};

#endif