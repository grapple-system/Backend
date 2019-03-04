#include "realPC.hpp"

RealPC::RealPC(string constraint) {

    genConst_set(constraint);

    int split = constraint.find("#(");
    string str;
    while(split!=-1){
        int start=split+1;
        split = constraint.find("#(",start);
        if(split!=-1){
            str=constraint.substr(start,split-start);
        }else{
            str=constraint.substr(start);
        }
        assert_cons.insert(str);
    }
}

void RealPC::genConst_set(string constraint) {
    int split= constraint.find(" ");
    while(split!=-1){
        int start=split+1;
        if(constraint.c_str()[start]==' '||constraint.c_str()[start]=='('||constraint.c_str()[start]=='-'||(constraint.c_str()[start]>='0'&&constraint.c_str()[start]<='9')){
            split = constraint.find(" ", start+1);
            continue;
        }
        int end1 = constraint.find(" ",start);
        int tmp = constraint.find("#",start);
        if(tmp!=-1&&tmp<end1){
            end1 = tmp;
        }
        int end2 = constraint.find(")",start);
        string var;
        if(end1>start){
            if(end2>start){
                if(end1>end2){
                    var = constraint.substr(start,end2-start);
                } else{
                    var = constraint.substr(start,end1-start);
                }
            }else{
                var = constraint.substr(start,end1-start);
            }
        }else if(end2>start){
            var = constraint.substr(start,end2-start);
        }
        if((var.length()==4&&strncmp(var.c_str(),"true",4)==0)||(var.length()==5&&strncmp(var.c_str(),"false",5)==0)){ continue;}

        if(strncmp(var.c_str(),"$D",2)==0||strncmp(var.c_str(),"$F",2)==0){
            const_real.insert(var);
        }else if(strncmp(var.c_str(),"$bv",3)==0){
            const_bvec.insert(var);
        }else if(strncmp(var.c_str(),"#x",2)==0){

        }else{
            const_int.insert(var);
        }

        split = constraint.find(" ", start+1);
    }
}
