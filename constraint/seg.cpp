#include "seg.hpp"
#include "z3++.h"

SEGraph::SEGraph(string filepath) {
    this->constraintMaps = ConstraintMaps(filepath);
    //constraintMaps.print();
}

RealPC SEGraph::retrieveConstraint(PseudoPC constRep) {
    list<Unit> units = constRep.getUnits();
    string constraint = constraintMaps.getConstraint(units);
    return RealPC (constraint);
}

// bool SEGraph::solve(RealPC rc) {
//     // set<string> ints = rc.getConst_int();
//     // long pid = pthread_self();
//     // stringstream ss;
//     // string tempFile;
//     // ss<<"cons"<<pid<<".smt2";
//     // ss>>tempFile;
//     // string cmd_z3 = "z3 -T:1 -smt2 "+tempFile;

//     // ofstream output(tempFile);
//     // if(!output){
//     //     cout<<"Failed to create file"<<endl;
//     //     return true;
//     // }
//     // for(set<string>::iterator ite=ints.begin();ite!=ints.end();++ite){
//     //     output<<"(declare-const "<<*ite<<" Int)"<<endl;
//     // }
//     // set<string> reals = rc.getConst_real();
//     // for(set<string>::iterator ite=reals.begin();ite!=reals.end();++ite){
//     //     output<<"(declare-const "<<*ite<<" Real)"<<endl;
//     // }
//     // set<string> asserts = rc.getAssert_cons();
//     // for(set<string>::iterator ite=asserts.begin();ite!=asserts.end();++ite){
//     //     output<<"(assert "<<*ite<<")"<<endl;
//     // }
//     // output<<"(check-sat)"<<endl;
//     // //output<<"(get-model)"<<endl;
//     // output.close();

//     // FILE *fp;
//     // char res[16];
//     // fp = popen(cmd_z3.c_str(), "r");
//     // if (fp != NULL)
//     // {
//     //     fgets(res, sizeof(res), fp);
//     //     pclose(fp);
//     // }
//     // remove(tempFile.c_str());

//     // if(strncmp(res,"sat",3)==0) {
//     //     //cout<<"true"<<endl;
//     //     return true;
//     // }else if(strncmp(res,"unknown",7)==0) {
//     //     //cout<<"true"<<endl;
//     //     return true;
//     // }else {
//     //     //cout<<"false"<<endl;
//     //     return false;
//     // }

//     long pid = (long)pthread_self();
//     stringstream ss;
//     string tempFile;
//     ss<<"cons"<<pid<<".smt2";
//     ss>>tempFile;

//     ofstream output(tempFile);
//     if(!output){
//         cout<<"Failed to create file"<<endl;
//         return true;
//     }
//     set<string> ints = rc.getConst_int();
//     for(set<string>::iterator ite=ints.begin();ite!=ints.end();++ite){
//         output<<"(declare-const "<<*ite<<" Int)"<<endl;
//     }
//     set<string> reals = rc.getConst_real();
//     for(set<string>::iterator ite=reals.begin();ite!=reals.end();++ite){
//         output<<"(declare-const "<<*ite<<" Real)"<<endl;
//     }
//     set<string> bvecs = rc.getConst_bvec();
//     for(set<string>::iterator ite=bvecs.begin();ite!=bvecs.end();++ite){
//         output<<"(declare-const "<<*ite<<" (_ BitVec 4))"<<endl;
//     }
//     set<string> asserts = rc.getAssert_cons();
//     for(set<string>::iterator ite=asserts.begin();ite!=asserts.end();++ite){
//         output<<"(assert "<<*ite<<")"<<endl;
//     }
//     output.close();

//     bool ret = false;

//     try {
//         z3::set_param("timeout", 1000);
//         z3::context c;
//         z3::solver s(c);
//         z3::expr_vector ev = c.parse_file(tempFile.c_str());
//         for (int i = 0; i < ev.size(); i++)
//             s.add(ev[i]);
//         switch(s.check()) {
//             case z3::sat: ret=true;break;
//             case z3::unsat: ret=false;break;
//             case z3::unknown: ret=true;break;
//         }
//     }
//     catch (z3::exception e) {
//         // cout << e.msg();
//         // ifstream fin(tempFile);
//         // string sin;
//         // while (getline(fin, sin))
//         //     cout << sin << endl;
//         // fin.close();
//     }

//     remove(tempFile.c_str());
//     return ret;
// }

bool SEGraph::solve(RealPC rc) {
    stringstream ss;
    string str;
    set<string> ints = rc.getConst_int();
    for(set<string>::iterator ite=ints.begin();ite!=ints.end();++ite){
        ss<<"(declare-const "<<*ite<<" Int) ";
    }
    set<string> reals = rc.getConst_real();
    for(set<string>::iterator ite=reals.begin();ite!=reals.end();++ite){
        ss<<"(declare-const "<<*ite<<" Real) ";
    }
    set<string> bvecs = rc.getConst_bvec();
    for(set<string>::iterator ite=bvecs.begin();ite!=bvecs.end();++ite){
        ss<<"(declare-const "<<*ite<<" (_ BitVec 4)) ";
    }
    set<string> asserts = rc.getAssert_cons();
    for(set<string>::iterator ite=asserts.begin();ite!=asserts.end();++ite){
        ss<<"(assert "<<*ite<<") ";
    }
    str=ss.str();

    bool ret = false;

    try {
        z3::set_param("timeout", 1000);
        z3::context c;
        z3::solver s(c);
        z3::expr_vector ev = c.parse_string(str.c_str());
        for (int i = 0; i < ev.size(); i++)
            s.add(ev[i]);
        switch(s.check()) {
            case z3::sat: ret=true;break;
            case z3::unsat: ret=false;break;
            case z3::unknown: ret=true;break;
        }
    }
    catch (z3::exception e) {
        // cout << e.msg();
        // cout << str << endl;
    }

    return ret;
}
