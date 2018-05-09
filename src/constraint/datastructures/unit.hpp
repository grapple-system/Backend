/**
 * Created by wangyifei on 2018/4/2.
 */

#ifndef UNIT_HPP_
#define UNIT_HPP_

#include "../common.hpp"


class Unit {
private:
    pair<int, int> pair1,pair2;
public:
    //(left1, left2), (right1, right2)
    Unit(int left1, int left2, int right1, int right2){
        this->pair1.first = left1;
        this->pair1.second = left2;
        this->pair2.first = right1;
        this->pair2.second = right2;
    }

    pair<int, int> getPair1(){
        return pair1;
    }

    pair<int, int> getPair2(){
        return pair2;
    }
};

#endif