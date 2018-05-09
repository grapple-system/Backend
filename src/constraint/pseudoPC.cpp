#include "pseudoPC.hpp"

PseudoPC::PseudoPC(std::string constr) {
        // TODO: implement pseudoPC initialization
    // [(left1,left2), (right1,right2)]
    int split1 = constr.find(",");
    int split2 = constr.find(",", split1+1);
    int split3 = constr.find(",", split2+1);
    int left1 = atoi(constr.substr(2,split1).c_str());
    int left2 = atoi(constr.substr(split1+1, split2-1).c_str());
    int right1 = atoi(constr.substr(split2+3, split3).c_str());
    int right2 = atoi(constr.substr(split3+1,constr.size()-2).c_str());
    this->units.push_back(Unit(left1,left2,right1,right2));
    cout<<left1<<left2<<right1<<right2<<endl;
}
