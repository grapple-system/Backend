/**
 * Created by wangyifei on 2018/4/2.
 */

#include "constraintMaps.hpp"

ConstraintMaps::ConstraintMaps(string filename1, string filename2) {
    ifstream input1(filename1);
    ifstream input2(filename2);
    if(!input1) {
        cout<<"Failed to open "<<filename1<<endl;
        if(!input2) {
            cout << "Failed to open " << filename2 << endl;
        }
        return;
    }
    if(!input2){
        cout<<"Failed to open "<<filename2<<endl;
        return;
    }
    string str;
    while(getline(input2,str)){
        int split1 = str.find_first_of(":");
        char *i;
        int index = atoi(str.substr(0, split1-1).c_str());
        string func = str.substr(split1+2, str.size());
        //cout<<index<<func<<"#"<<endl;
        func2indexMap[func]=index;
    }
    while(getline(input1,str)){
        string signature = str;
        int funcIndex = this->func2indexMap[str];
        map<int, ConstraintNode> constraintMap;
        list<string> stateNodeList;
        while(getline(input1,str)){
            //cout<<str<<endl;
            if(str.size()==0)break;
            stateNodeList.push_back(str);
        }
        list<string>::iterator itr = stateNodeList.begin();
        setConstraint(constraintMap, 0, itr);

        this->constraintMaps[funcIndex]=constraintMap;
        stateNodeList.clear();
        //constraintMap.clear();
    }
//    Unit unit1("<Test0: void nest_for(int)>", 1, 38);
//    Unit unit2("<Test0: void while_dowhile(int,int)>", 2, 48);
//    list<Unit> units;
//    units.push_back(unit1);
//    units.push_back(unit2);
//    cout<<getConstraint(unit1)<<endl;
//    cout<<getConstraint(unit2)<<endl;
//    cout<<getConstraint(units)<<endl;
}

string ConstraintMaps::getConstraint(Unit unit) {
    int funcIndex = unit.getPair1().first;
    int start = unit.getPair1().second;
    int end = unit.getPair2().second;
    if(!constraintMaps[funcIndex].size()) return NULL;

    if(start == (end-1)/2){
        if(end == start*2+1){
            return constraintMaps[funcIndex][start].getConditional();
        } else{
            return "(not "+constraintMaps[funcIndex][start].getConditional()+")";
        }
    }
    return "";
//    else if(start < (end-1)/2){
//        return getConstraint(Unit(str, start, (end-1)/2)) + " && " + getConstraint(Unit(str, (end-1)/2, end));
//    }else {
//        // error
//        return "";
//    }
}

string ConstraintMaps::getConstraint(list<Unit> units) {
    list<Unit>::iterator itr = units.begin();
    string str = getConstraint(*itr);
    ++itr;
    while(itr != units.end()){
        string str = getConstraint(*itr);
        if(str.size())
            str.append(" && " + getConstraint(*itr));
        ++itr;
    }
    return str;
}

void ConstraintMaps::setConstraint(map<int, ConstraintNode> &constraintMap, int i, list<string>::iterator &itr) {
    ptree pt;
    string str = *itr;
    ++itr;

    stringstream ss(str);
    try{
        read_json(ss, pt);
    } catch(ptree_error & e) {
        cout<<"Failed to read json"<<endl;
    }
    try{
        ptree pt1 = pt.get_child("stateNode");
        if(pt1.empty()){
            return;
        }else {
            //get conditional
            constraintMap[i] = ConstraintNode(pt1);

            setConstraint(constraintMap, 2*i+1, itr);
            setConstraint(constraintMap, 2*i+2, itr);
            return;
        }

    } catch (ptree_error & e) {
        cout<<"Failed to get value: "<<endl;
    }
}

void ConstraintMaps::print() {
    map<int, map<int, ConstraintNode>>::iterator itr0 = constraintMaps.begin();
    while(itr0!=constraintMaps.end()){
        cout<<itr0->first<<endl;
        map<int, ConstraintNode>::iterator itr1 = itr0->second.begin();
        while(itr1!=itr0->second.end()) {
            int start = itr1->first;
            string constraint = itr1->second.getConditional();
            if (constraint.size() != 0){
                cout << "\t[" << start << ", " << start * 2 + 1 << "]: " << constraint << endl;
                cout << "\t[" << start << ", " << start * 2 + 2 << "]: !" << constraint << endl;
            }
            ++itr1;
        }
        cout<<endl;
        ++itr0;
    }
}