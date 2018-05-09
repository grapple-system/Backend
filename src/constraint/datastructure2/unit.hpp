/**
 * Created by wangyifei on 2018/4/2.
 */

#ifndef UNIT_HPP_
#define UNIT_HPP_

#include <string>
using  namespace std;

struct Pair{
    int index1;
    int index2;
};

class Unit {
private:
    Pair pair1,pair2;
public:
    //(left1, left2), (right1, right2)
    Unit(int left1, int left2, int right1, int right2){
        this->pair1.index1 = left1;
        this->pair1.index2 = left2;
        this->pair2.index1 = right1;
        this->pair2.index2 = right2;
    }

    Pair getPair1(){
        return pair1;
    }

    Pair getPair2(){
        return pair2;
    }
};

#endif